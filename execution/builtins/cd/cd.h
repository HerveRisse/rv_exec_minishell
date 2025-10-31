
#ifndef CD_H
#define CD_H

#include "../../execution.h"

int cd_handle_home(t_shell *shell, char **path);
int cd_handle_oldpwd(t_shell *shell, char **path);
int cd_get_path(t_command *cmd, t_shell *shell, char **path);
int cd_change_directory(char *path, char *old_pwd);
void update_pwd_vars(t_shell *shell, char *old_pwd);
int cd_special_dash(t_shell *shell);
int cd_normal_case(t_command *cmd, t_shell *shell);

#endif
