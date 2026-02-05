#include "manager.h"
#include "clipboard.h"
#include "file.h"
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector *read_from_file() {
  vector *locations_vec = create_vector(sizeof(location));
  if (!file_exists(FILENAME)) {
    return locations_vec;
  }
  FILE *read_file = fopen(FILENAME, "rb");
  if (read_file == NULL) {
    return locations_vec;
  }

  size_t num_locations;
  fread(&num_locations, sizeof(size_t), 1, read_file);

  for (size_t i = 0; i < num_locations; i++) {
    location loc;

    size_t name_len;
    fread(&name_len, sizeof(size_t), 1, read_file);
    loc.name = malloc(name_len + 1);
    fread(loc.name, sizeof(char), name_len, read_file);
    loc.name[name_len] = '\0';

    loc.accounts = create_vector(sizeof(account));

    size_t num_accounts;
    fread(&num_accounts, sizeof(size_t), 1, read_file);

    for (size_t j = 0; j < num_accounts; j++) {
      account acc;

      size_t username_len;
      fread(&username_len, sizeof(size_t), 1, read_file);
      acc.username = malloc(username_len + 1);
      fread(acc.username, sizeof(char), username_len, read_file);
      acc.username[username_len] = '\0';

      size_t password_len;
      fread(&password_len, sizeof(size_t), 1, read_file);
      acc.password = malloc(password_len + 1);
      fread(acc.password, sizeof(char), password_len, read_file);
      acc.password[password_len] = '\0';

      vec_push(loc.accounts, &acc);
    }

    vec_push(locations_vec, &loc);
  }

  fclose(read_file);
  return locations_vec;
}
void write_to_file(vector *locations_vec) {
  FILE *write_file = fopen(FILENAME, "wb");
  if (write_file == NULL) {
    return;
  }

  size_t count = vec_count(locations_vec);
  fwrite(&count, sizeof(size_t), 1, write_file);

  for (size_t i = 0; i < count; i++) {
    location *loc = (location *)vec_at(locations_vec, i);

    size_t name_len = strlen(loc->name);
    fwrite(&name_len, sizeof(size_t), 1, write_file);
    fwrite(loc->name, sizeof(char), name_len, write_file);

    size_t num_accounts = vec_count(loc->accounts);
    fwrite(&num_accounts, sizeof(size_t), 1, write_file);

    for (size_t j = 0; j < num_accounts; j++) {
      account *acc = (account *)vec_at(loc->accounts, j);

      size_t username_len = strlen(acc->username);
      fwrite(&username_len, sizeof(size_t), 1, write_file);
      fwrite(acc->username, sizeof(char), username_len, write_file);

      size_t password_len = strlen(acc->password);
      fwrite(&password_len, sizeof(size_t), 1, write_file);
      fwrite(acc->password, sizeof(char), password_len, write_file);
    }
  }

  fclose(write_file);
}

void list(vector *locations_vec) {
  if (vec_count(locations_vec) == 0) {
    printf("No stored accounts currently exists\n");
  }
  for (int i = 0; i < vec_count(locations_vec); i++) {
    location *loc = (location *)vec_at(locations_vec, i);
    printf("Location : %s\n", loc->name);
    for (int j = 0; j < vec_count(loc->accounts); j++) {
      account *acc = (account *)vec_at(loc->accounts, j);
      printf("    Username : %s\n", acc->username);
    }
  }
}

void list_by_location(vector *locations_vec, char *location_name) {
  for (int i = 0; i < vec_count(locations_vec); i++) {
    location *loc = (location *)vec_at(locations_vec, i);
    if (strcmp(loc->name, location_name) == 0) {
      printf("Location : %s\n", loc->name);
      for (int j = 0; j < vec_count(loc->accounts); j++) {
        account *acc = (account *)vec_at(loc->accounts, j);
        printf("    Username : %s\n", acc->username);
      }
      return;
    }
  }
  printf("No location exists with Name : %s\n", location_name);
}

void get_by_username(vector *locations_vec, char *location_name,
                     char *username) {
  for (int i = 0; i < vec_count(locations_vec); i++) {
    location *loc = (location *)vec_at(locations_vec, i);
    if (strcmp(loc->name, location_name) == 0) {
      for (int j = 0; j < vec_count(loc->accounts); j++) {
        account *acc = (account *)vec_at(loc->accounts, j);
        if (strcmp(acc->username, username) == 0) {
          printf("Location : %s\n", loc->name);
          printf("    Username : %s\n", acc->username);
          copy_to_clipboard(acc->password);
          return;
        }
      }
    }
  }
  printf("No account exists with Username : %s\n", username);
}

void create_account(vector *locations_vec, char *location_name, char *username,
                    char *password) {
  for (int i = 0; i < vec_count(locations_vec); i++) {
    location *loc = (location *)vec_at(locations_vec, i);
    if (strcmp(location_name, loc->name) == 0) {
      for (int j = 0; j < vec_count(loc->accounts); j++) {
        account *acc_existing = (account *)vec_at(loc->accounts, j);
        if (strcmp(username, acc_existing->username) == 0) {
          printf("Username '%s' already exists in the location : %s\n",
                 username, loc->name);
          return;
        }
      }
      account new_acc = {username, password};
      vec_push(loc->accounts, &new_acc);
    }
  }
  location new_loc = {location_name, create_vector(sizeof(account))};
  account new_acc = {username, password};
  vec_push(new_loc.accounts, &new_acc);
  vec_push(locations_vec, &new_loc);
  write_to_file(locations_vec);
}

void delete_by_location(vector *locations_vec, char *location_name) {
  for (int i = 0; i < vec_count(locations_vec); i++) {
    location *loc = (location *)vec_at(locations_vec, i);
    if (strcmp(loc->name, location_name) == 0) {
      printf("Deleting all accounts related to Location '%s'\n", loc->name);
      free_vector(&loc->accounts);
      vec_remove_at(locations_vec, i);
      printf("Deleted sucessfully\n");
      return;
    }
  }
  printf("No location exists with Name : %s\n", location_name);
}

void delete_by_username(vector *locations_vec, char *location_name,
                        char *username) {
  for (int i = 0; i < vec_count(locations_vec); i++) {
    location *loc = (location *)vec_at(locations_vec, i);
    if (strcmp(loc->name, location_name) == 0) {
      printf("Deleting account '%s' related to Location '%s'\n", username,
             loc->name);
      for (int j = 0; j < vec_count(loc->accounts); j++) {
        account *acc = (account *)vec_at(loc->accounts, j);
        if (strcmp(acc->username, username) == 0) {
          vec_remove_at(loc->accounts, j);
          printf("Deleted sucessfully\n");
          return;
        }
      }
    }
  }
  printf("No account exists of Location '%s' with Username : %s\n",
         location_name, username);
}
