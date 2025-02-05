/**
 *
 *  @title{libuserlinux: API to add or delete Linux users}
 * 	This code implements Linux user management functions.
 * 
 *  @brief   Linux User Management Support
 *  @file    libuserlinux.h
 *  @author  Eduardo Gerhardt (comercial.eduardogerhardt@gmail.com)
 *
 */

/* ****************
 * INCLUDED FILES *
 * ****************/

#include <stdbool.h>
 
/* *********************************
 * DEFINITION OF PUBLIC STRUCTURES *
 * *********************************/

typedef struct {
	char *pszUserName;
	char *pszUserPassword;
	unsigned int uiUserID;
	unsigned int uiGroupID;
	char *pszUserInfo;
	char *pszUserDir;
	bool bEnableEncryption;
}stUserData;

/* ********************************
 * PROTOTYPES OF PUBLIC FUNCTIONS *
 * ********************************/

/**
 * @title{Linux User Manager - Add New User}
 *
 * This function check if a user exists in Linux.
 * @param[in] pszCheckUsername - Username to check.
 * @return Returns 0 in success.
 * @return Returns 22 (EINVAL) invalid argument.
 */
int libuserlinux_checkuser(char *pszCheckUsername);

/**
 * @title{Linux User Manager - Add New User}
 *
 * This function creates a new user in Linux.
 * @param[in] pszUserName - Username.
 * @param[in] pszUserPassword - User password.
 * @param[in] uiUserID - User ID.
 * @param[in] uiGroupID - Group ID.
 * @param[in] pszUserInfo - User info.
 * @param[in] pszUserDir - User directory.
 * @param[in] bEnableEncryption - Encrypt the password.
 * @return Returns 0 in success.
 * @return Returns 22 (EINVAL) invalid argument.
 * @return Returns 13 (EACCES) error accessing a file.
 */
int libuserlinux_adduser(stUserData *pstUserData);

/**
 * @title{Linux User Manager - Delete User}
 *
 * This function delete a user in Linux.
 */
int libuserlinux_deluser(char *pszUsername);

/**
 * @title{Linux User Manager - Change user password}
 *
 * This function change a user's password.
 */
int libuserlinux_changepassword(char *pszUsername, char *pszNewPasswd);

/**
 * @title{Linux User Manager - Check if user exists}
 *
 * This function check if user exists.
 */
int libuserlinux_checkuser(char *pszUsername);
