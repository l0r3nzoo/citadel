#ifndef PASSWORD_H
#define PASSWORD_H

#include "vector.h"

#define FILENAME "passwords.enc"
typedef struct {
  char *username;
  char *password;
} account;

typedef struct {
  char *name;
  vector *accounts;
} location;

void write_to_file(vector *locations_vec);
vector* read_from_file();
void list(vector *locations_vec);
void list_by_location(vector *locations_vec,char *location_name);
void delete_by_location(vector *locations_vec,char *location_name);
void create_account(vector *locations_vec,char *location_name, char *username, char *password);
void get_by_username(vector *locations_vec,char*location_name,char *username);
void delete_by_username(vector *locations_vec,char*location_name,char *username);
void update_password(vector *locations_vec,char*location_name,char *username,char* new_password);

#endif
