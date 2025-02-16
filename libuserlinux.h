/*
 *
 * Module: libuserlinux.h
 * Description: API for managing Linux users.
 *
 * This header defines structures and function prototypes for adding,
 * deleting, and modifying user accounts and passwords in a custom Linux
 * environment.
 *
 * Author: Eduardo Gerhardt (comercial.eduardogerhardt@gmail.com)
 *
 */

#ifndef LIBUSERLINUX_H
#define LIBUSERLINUX_H

/*==============================================================================
                          INCLUDES
==============================================================================*/

#include <stdbool.h>

/*==============================================================================
                          PUBLIC STRUCTURES
==============================================================================*/

typedef struct {
	char *pszUserName;
	char *pszUserPassword;
	unsigned int uiUserID;
	unsigned int uiGroupID;
	char *pszUserInfo;
	char *pszUserDir;
	bool bEnableEncryption;
} stUserData;

/*==============================================================================
                         FUNCTION PROTOTYPES
==============================================================================*/

/**
 * Linux User Manager - Add New User
 *
 * This function check if a user exists in Linux.
 *
 * @param pszCheckUsername - Username to check.
 * @return Returns 0 in success.
 * @return Returns 22 (EINVAL) invalid argument.
 */
int libuserlinux_checkuser(char *pszCheckUsername);

/**
 * Linux User Manager - Add New User
 *
 * This function creates a new user in Linux.
 *
 * @param] pszUserName - Username.
 * @param] pszUserPassword - User password.
 * @param] uiUserID - User ID.
 * @param] uiGroupID - Group ID.
 * @param] pszUserInfo - User info.
 * @param] pszUserDir - User directory.
 * @param] bEnableEncryption - Encrypt the password.
 * @return Returns 0 in success.
 * @return Returns 22 (EINVAL) invalid argument.
 * @return Returns 13 (EACCES) error accessing a file.
 */
int libuserlinux_adduser(stUserData *pstUserData);

/**
 * Linux User Manager - Delete User
 *
 * This function delete a user in Linux.
 */
int libuserlinux_deluser(char *pszUsername);

/**
 * Linux User Manager - Change user password
 *
 * This function change a user's password.
 */
int libuserlinux_changepassword(char *pszUsername, char *pszNewPasswd);


/**
 * Linux User Manager - Check if user exists
 *
 * This function check if user exists.
 */
int libuserlinux_checkuser(char *pszUsername);

#endif /* LIBUSERLINUX_H */