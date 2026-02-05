#include "file.h"
#include "manager.h"
#include "vector.h"
#include <stdio.h>
#include <string.h>

int main() {
	printf("-------------Citadel Password Manager-------------\n");
	printf("    [1] Search All\n");
	printf("    [2] Search By Location\n");
	printf("    [3] Search By Username\n");
	printf("    [4] Create New Account\n");
	printf("    [5] Delete All\n");
	printf("    [6] Delete By Location\n");
	printf("    [7] Delete By Username\n");
	printf("    [8] Update Password\n");
	printf("    [q] Quit Application\n");
	while (1) {
		char option_buffer[16];
		printf("Please choose an option : ");
		fgets(option_buffer, sizeof(option_buffer), stdin);
		option_buffer[strcspn(option_buffer, "\n")] = '\0';

		vector *locations_vec = read_from_file();

		if (strcmp(option_buffer, "1") == 0) { // search all
			list(locations_vec);
		}


		else if (strcmp(option_buffer, "2") == 0) { // search by location
			char location_buffer[64];
			printf("[Read By Location] Please enter location name : ");
			fgets(location_buffer, sizeof(location_buffer), stdin);
			location_buffer[strcspn(location_buffer, "\n")] = '\0';
			list_by_location(locations_vec, location_buffer);
		}


		else if (strcmp(option_buffer, "3") == 0) { // search by username
			char location_buffer[64];
			char username_buffer[1024];
			printf("[Read By Username] Please enter location name : ");
			fgets(location_buffer, sizeof(location_buffer), stdin);
			location_buffer[strcspn(location_buffer, "\n")] = '\0';
			printf("[Read By Username] Please enter account username : ");
			fgets(username_buffer, sizeof(username_buffer), stdin);
			username_buffer[strcspn(username_buffer, "\n")] = '\0';
			get_by_username(locations_vec, location_buffer,username_buffer);
		}


		else if (strcmp(option_buffer, "4") == 0) { // create new account
			char location_buffer[64];
			char username_buffer[1024];
			char password_buffer[1024];
			printf("[Create Account] Please enter your account details\n");
			printf("[Create Account] Location : ");
			fgets(location_buffer, sizeof(location_buffer), stdin);
			location_buffer[strcspn(location_buffer, "\n")] = '\0';
			printf("[Create Account] Username : ");
			fgets(username_buffer, sizeof(username_buffer), stdin);
			username_buffer[strcspn(username_buffer, "\n")] = '\0';
			printf("[Create Account] Password : ");
			fgets(password_buffer, sizeof(password_buffer), stdin);
			password_buffer[strcspn(password_buffer, "\n")] = '\0';
			create_account(locations_vec, location_buffer, username_buffer,
					password_buffer);
		}


		else if (strcmp(option_buffer, "5") == 0) { // delete all
			if (file_exists(FILENAME)) {
				if (file_delete(FILENAME) == 0) {
					printf("[Delete All] Deleted all accounts sucessfully\n");
				}
			} else {
				printf("[Delete All] Meta File doesn't exist, No need for deletion\n");
			}
		}


		else if (strcmp(option_buffer, "6") == 0) { // delete by location
			char location_buffer[64];
			printf("[Delete By Location] Please enter location name : ");
			fgets(location_buffer, sizeof(location_buffer), stdin);
			location_buffer[strcspn(location_buffer, "\n")] = '\0';
			delete_by_location(locations_vec, location_buffer);
		}

		else if (strcmp(option_buffer, "7") == 0) { // delete by username
			char location_buffer[64];
			char username_buffer[1024];
			printf("[Delete By Username] Please enter location name : ");
			fgets(location_buffer, sizeof(location_buffer), stdin);
			location_buffer[strcspn(location_buffer, "\n")] = '\0';
			printf("[Delete By Username] Please enter account username : ");
			fgets(username_buffer, sizeof(username_buffer), stdin);
			username_buffer[strcspn(username_buffer, "\n")] = '\0';
			delete_by_username(locations_vec, location_buffer, username_buffer);
		}

		else if (strcmp(option_buffer, "8") == 0) { 
			char location_buffer[64];
			char username_buffer[1024];
			char new_password_buffer[1024];
			printf("[Update Password] Please enter location name : ");
			fgets(location_buffer, sizeof(location_buffer), stdin);
			location_buffer[strcspn(location_buffer, "\n")] = '\0';
			printf("[Update Password] Please enter account username : ");
			fgets(username_buffer, sizeof(username_buffer), stdin);
			username_buffer[strcspn(username_buffer, "\n")] = '\0';
			printf("[Update Password] Please enter new account password : ");
			fgets(new_password_buffer, sizeof(new_password_buffer), stdin);
			new_password_buffer[strcspn(new_password_buffer, "\n")] = '\0';
			update_password(locations_vec,location_buffer,username_buffer,new_password_buffer);
		}


		else if (strcmp(option_buffer, "q") == 0) { // quit
			return 0;
		}



		else {
			printf("Option is not valid, Please choose a valid option.\n");
		}
	}
	return 0;
}
