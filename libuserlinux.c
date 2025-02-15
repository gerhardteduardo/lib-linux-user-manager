/*
 *
 * Module: libuserlinux.c
 * Description: API for managing Linux users.
 *
 * This module implements functions for adding, deleting, and modifying user
 * accounts and passwords in a custom Linux environment.
 *
 * Author: Eduardo Gerhardt (comercial.eduardogerhardt@gmail.com)
 *
 */

/*==============================================================================
                          INCLUDES
==============================================================================*/

/* Dependencies: */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <shadow.h>
#include <unistd.h>
#include <crypt.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <pthread.h>
#include <ctype.h>

/* Implements: */
#include "libuserlinux.h"

/*==============================================================================
                           PRIVATE DEFINES
==============================================================================*/

/**
 * @brief This path contains the Linux user database
 **/
#define PATH_PASSWD				"/mnt/internal/config/passwd"

/**
 * @brief This path contains the Linux user password database
 **/
#define PATH_SHADOW				"/mnt/internal/config/shadow"

/**
 * @brief This path contains the Linux user temp database
 **/
#define PATH_PASSWD_TMP				"/mnt/internal/config/passwd_tmp"

/**
 * @brief This path contains the Linux user temp password database
 **/
#define PATH_SHADOW_TMP				"/mnt/internal/config/shadow_tmp"

/**
 * @brief Salt used to perturb the encoding algorithm
 **/
#define SALT_VALUE				"212021918"

/**
 * @brief User command interpreter
 **/
#define USER_INTERPRETER		"/bin/sh"

/*==============================================================================
                           PRIVATE FUNCTIONS
==============================================================================*/

/**
 * @brief This function encrypts the user's pa ssword.
 *
 * @param pszUserPassword - User password.
 * @return Returns encrypted password.
 */
static char* libuserlinux_encrypt_password(char *pszUserPassword)
{
	return crypt(pszUserPassword, SALT_VALUE);
}

/**
 * @brief This function add username in database.
 *
 * @param pszUserName - Username.
 * @param pszUserPassword - User password.
 * @param bEnableEncryption - Encrypt the password.
 * @return Returns 0 in success.
 * @return Returns -22 (EINVAL) invalid argument.
 * @return Returns -13 (EACCES) permission denied.
 */
static int libuserlinux_addusername_database(stUserData *pstUserData)
{
	int iRet = -1;
	FILE *fpPasswd = NULL;	
    struct passwd *pwd;

	if (pstUserData != NULL) {
		pwd = getpwent();
		if (pwd != NULL) {
			pwd->pw_name = pstUserData->pszUserName;		
			pwd->pw_passwd[0] = 'x';
			pwd->pw_passwd[1] = '\0';
			pwd->pw_gid = pstUserData->uiUserID;
			pwd->pw_uid = pstUserData->uiGroupID;
			pwd->pw_gecos = pstUserData->pszUserInfo;
			pwd->pw_dir = pstUserData->pszUserDir;
			pwd->pw_shell = strdup(USER_INTERPRETER);
			
			fpPasswd = fopen(PATH_PASSWD, "a");
			if (fpPasswd != NULL) {
				flockfile(fpPasswd);
				putpwent(pwd, fpPasswd);
				funlockfile(fpPasswd);
				fclose(fpPasswd);
				iRet = 0;
			}
			else {
				iRet = -EACCES;
			}
			free(pwd->pw_shell);
			endpwent();	
		}
		else {
			iRet = -EINVAL;
		}
	}
	else {
		iRet = -EINVAL;
	}

    return iRet;
}

/**
 * @brief This function add user password.
 *
 * @param pszUserName - Username.
 * @param pszUserPassword - User password.
 * @param bEnableEncryption - Encrypt the password.
 * @return Returns 0 in success.
 * @return Returns -22 (EINVAL) invalid argument.
 * @return Returns -13 (EACCES) permission denied.
 */
static int libuserlinux_addpasswd_database(stUserData *pstUserData)
{
	int iRet = -1;
	FILE *fpShadow = NULL;
	char *pszEncryptedPassword = NULL;
	struct spwd *spd;

	if (pstUserData != NULL) {
		spd = getspent();
    	if (spd != NULL) {
			if (pstUserData->bEnableEncryption) {
				pszEncryptedPassword = libuserlinux_encrypt_password(pstUserData->pszUserPassword);
			}
			else {
				pszEncryptedPassword = pstUserData->pszUserPassword;
			}
			spd->sp_namp = pstUserData->pszUserName;
			spd->sp_pwdp = pszEncryptedPassword;
			/* spd->sp_lstchg = NULL;
			spd->sp_min = NULL;
			spd->sp_max = NULL;
			spd->sp_warn = NULL;
			spd->sp_inact = NULL;
			spd->sp_expire = NULL;
			spd->sp_flag = NULL; */
			
			fpShadow = fopen(PATH_SHADOW, "a");
			if (fpShadow != NULL) {
				flockfile(fpShadow);
				putspent(spd, fpShadow);
				funlockfile(fpShadow);
				fclose(fpShadow);
				iRet = 0;
			}
			else {
				iRet = -EACCES;
			}
			endspent();
		}
		else {
			iRet = -EINVAL;
		}
	}
	else {
		iRet = -EINVAL;
	}
	
	return iRet;
}

/**
 * @brief  This function delete username from database.
 *
 * @param pszUserName - Username.
 * @return Returns 0 in success.
 * @return Returns -22 (EINVAL) invalid argument.
 * @return Returns -13 (EACCES) permission denied.
 */
static int libuserlinux_delusername_database(char *pszUsername)
{
	int iRet = -1;
	char szLine[1024];
	bool bUserDeleted = false;
	char *pszReadFile = NULL;
	FILE *fpPasswd = NULL;
	FILE *fpPasswdTmp = NULL;
	
	if (pszUsername != NULL) {
		fpPasswd = fopen(PATH_PASSWD, "r");
		if (fpPasswd != NULL) {
			flockfile(fpPasswd);
			fpPasswdTmp = fopen(PATH_PASSWD_TMP, "w");
			if (fpPasswdTmp != NULL) {
				while (fgets(szLine, sizeof(szLine), fpPasswd) != NULL) {
					if ((pszReadFile = strstr(szLine, pszUsername)) != NULL) {
						fprintf(fpPasswdTmp, "");
						bUserDeleted = true;
					}
					else {
						fprintf(fpPasswdTmp, "%s", szLine);
					}
				}
				fclose(fpPasswdTmp);
			}
			else {
				iRet = -EACCES;
			}
			funlockfile(fpPasswd);
			fclose(fpPasswd);
		}
		else {
			iRet = -EACCES;
		}
	}
	else {
		iRet = -EINVAL;
	}

	if (bUserDeleted) {
		remove(PATH_PASSWD);
		rename(PATH_PASSWD_TMP, PATH_PASSWD);
		iRet = 0;
	}

	return iRet;
}
 
 /**
 * @brief DThis function delete user password from database.
 *
 * @param pszUserName - Username. 
 * @return Returns 0 in success.
 * @return Returns -22 (EINVAL) invalid argument.
 * @return Returns -13 (EACCES) permission denied.
 */
static int libuserlinux_delpasswd_database(char *pszUsername)
{
	int iRet = -1;
	char szLine[1024];
	bool bPasswdDeleted = false;
	char *pszReadFile = NULL;
	FILE *fpShadow = NULL;
	FILE *fpShadowTmp = NULL;

	if (pszUsername != NULL) {
		fpShadow = fopen(PATH_SHADOW, "r");
		if (fpShadow != NULL) {
			flockfile(fpShadow);
			fpShadowTmp = fopen(PATH_SHADOW_TMP, "w");
			if (fpShadowTmp != NULL) {
				while (fgets(szLine, sizeof(szLine), fpShadow) != NULL) {
					if ((pszReadFile = strstr(szLine, pszUsername)) != NULL) {
						fprintf(fpShadowTmp, "");
						bPasswdDeleted = true;
					}
					else {
						fprintf(fpShadowTmp,"%s", szLine);
					}
				}
				fclose(fpShadowTmp);
			}
			else {
				iRet = -EACCES;
			}
			funlockfile(fpShadow);
			fclose(fpShadow);
		}
		else {
			iRet = -EACCES;
		}
	}
	else {
		iRet = -EINVAL;
	}

	if (bPasswdDeleted) {
		remove(PATH_SHADOW);
		rename(PATH_SHADOW_TMP, PATH_SHADOW);
		iRet = 0;
	}

	return iRet;
}

/*==============================================================================
                           PUBLIC FUNCTIONS
==============================================================================*/

/* See header file */
int libuserlinux_checkuser(char *pszCheckUsername)
{
	int iRet = -1;
	struct passwd *pwdcheck;

	if (pszCheckUsername != NULL) {
		pwdcheck = getpwent();
		if (pwdcheck != NULL) {
			pwdcheck = getpwnam(pszCheckUsername);
			if (pwdcheck != NULL) {
				iRet = 1;
			}
			else {
				iRet = 0;
			}
			endpwent();
		}
		else {
			iRet = -EINVAL;
		}
	}
	else {
		iRet = -EINVAL;
	}

	return iRet;
}

/* See header file */
int libuserlinux_adduser(stUserData *pstUserData)
{
	int iRet = -1;
	int iUserExists = -1;

	if (pstUserData != NULL) {
		iUserExists = libuserlinux_checkuser(pstUserData->pszUserName);
	}
	else {
		iRet = -EINVAL;
	}

	if (!iUserExists) {
		if (libuserlinux_addusername_database(pstUserData) == 0) {
			if (libuserlinux_addpasswd_database(pstUserData) == 0) {
				iRet = 0;
			}
			else {
				iRet = -EINVAL;
			}
		}
		else {
			iRet = -EINVAL;
		}
	}
	else {
		iRet = -EUSERS;
	}
	
    return iRet;
}

/* See header file */
int libuserlinux_deluser(char *pszUsername)
{
	int iRet = -1;
	int iUserExists = -1;

	if (pszUsername != NULL) {
		iUserExists = libuserlinux_checkuser(pszUsername);
	}
	else {
		iRet = -EINVAL;
	}

	if (iUserExists) {
		if (libuserlinux_delusername_database(pszUsername) == 0) {
			if (libuserlinux_delpasswd_database(pszUsername) == 0) {
				iRet = 0;
			}
			else {
				iRet = -EINVAL;
			}
		}
		else {
			iRet = -EINVAL;
		}
	}
	else {
		iRet = -EINVAL;
	}

	return iRet;
}

/* See header file */
int libuserlinux_changepassword(char *pszUsername, char *pszNewPasswd)
{
	int iRet = -1;
	FILE *fpShadow = NULL;
	char *pszEncryptedPassword = NULL;
	struct spwd *spd;

	if (pszUsername != NULL && pszNewPasswd != NULL) {
		spd = getspent();
		if (spd != NULL) {
			spd = getspnam(pszUsername);
			if (spd != NULL) {
				if (libuserlinux_delpasswd_database(pszUsername) == 0) {
					pszEncryptedPassword = libuserlinux_encrypt_password(pszNewPasswd);
					spd->sp_pwdp = pszEncryptedPassword;

					fpShadow = fopen(PATH_SHADOW, "a");
					if (fpShadow != NULL) {
						flockfile(fpShadow);
						putspent(spd, fpShadow);
						funlockfile(fpShadow);
						fclose(fpShadow);
						iRet = 0;
					}
					else {
						iRet = -EACCES;
					}
				}
				else {
					iRet = -EINVAL;
				}
			}
			else {
				iRet = -EINVAL;
			}
			endspent();
		}
		else {
			iRet = -EINVAL;
		}
	}
	else {
		iRet = -EINVAL;
	}

	return iRet;
}
