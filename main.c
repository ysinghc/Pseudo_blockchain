#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <unistd.h>

typedef struct transaction
{
    char debit_credit;
    float amount;
    char username_origin[20];
    char username_destination[20];
}
transaction;
typedef struct node
{
    char previous_node_hash[258];
    char node_hash[258];
    transaction data;
    char next_node[258];
}
node;

//sha256 hash function
char *sha256(char *str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    int i = 0;
    char *hash_str = (char *)malloc(SHA256_DIGEST_LENGTH * sizeof(char)*256);
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(hash_str + (i * 2), "%02x", hash[i]);
    }
    free(hash_str);
    return hash_str;
}
//login and signup validation
char losi(char *username, char *password)
{
    do
    {
        system("clear");
        printf("(L)ogin\n(S)ignup\n");
        char losi;
        scanf("%c", &losi);
        losi = tolower(losi);
        system("clear");
        
        if(losi == 'l'){
            printf("username:- ");
            scanf("%s",username);
            printf("password:- ");
            scanf("%s",password);
            return losi;
        }
        else if(losi == 's'){
            printf("username:- ");
            scanf("%s",username);
            printf("password:- ");
            scanf("%s",password);
            return losi;
        }
        else{
            continue;
        }
    
    }while(1);
}

//login and signup validation
int losin(void){
    //custom data-structure for profile
    typedef struct
    {
        char username[20];
        char password[16];
    }
    profile;
    profile template_profile;
    while(1){
        system("clear");
        char a = losi(&template_profile.username, &template_profile.password);
        if(a == 'l'){
            //opening database
            FILE *db = fopen("user_database.csv","r");
            //exceptional handling
            if(db == NULL){
                printf("Some error opening file\n");
                return 1;
            }
            //buffer for read
            char buffer[256];

            int row = -1;
            int column = 0;
            while(fgets(buffer, 256, db)){
                column = 0;
                row++;
                char *data = strtok(buffer, ", ");
                while(data){
                    if(strcmp(data,sha256(template_profile.username)) == 0){
                        data = strtok(NULL,", ");
                        if(strcmp(data, sha256(template_profile.password)) == 0){
                            printf("You are now logged in as %s\n",template_profile.username);
                            return 0; 
                        }
                        else{
                            printf("Either the password or the username is not correct");
                            system("clear");
                            continue;
                        }
                    }
                    data = strtok(NULL,", ");
                }
            }
            fclose(db);
            return 0;
        }
        else{
            //opening database
            FILE *db = fopen("user_database.csv","r+");
            //exceptional handling
            if(db == NULL){
                printf("Some error opening file\n");
                return 1;
            }
            //buffer for reading
            char buffer[256];

            int row = -1;

            while(fgets(buffer, 256, db)){
                row++;
                char *data = strtok(buffer, ", ");
                while(data){
                    if(strcmp(data,sha256(template_profile.username)) == 0){
                        printf("Username already exits");
                        system("clear");
                    }
                    data = strtok(NULL,", ");
                }
            }
        
            fprintf(db, "\n%s, %s,",sha256(template_profile.username), sha256(template_profile.password));
            printf("Account created\n");
        
            fclose(db);
        }
    }
}

int main(void){
    losin();
    return 0;
}