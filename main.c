#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_habit(int entry);
void show_detailed_report();
void show_detailed_report();
void register_report();
void list_habits();
void add_habit();

int main()
{
    int selectionMain = 0;
    int entry;
    char chr;
    int badge_counter = 0;
    int i=0;
    int bufferLength=64;
    char buffer[bufferLength];

    printf("Welcome to Habit Builder!\n\n");

    FILE *fp;

    if((fp = fopen("badges.txt","r"))!=NULL){

	if(fp != NULL){

	while (chr != EOF){
	//Count whenever new line is encountered
	    if (chr == '\n'){
	    badge_counter += 1;
	    }
	//take next character from file.
	    chr = getc(fp);
	}
	rewind(fp);

	printf("Badges:\n");

	for(i=0;i<badge_counter;i++){
	    fgets(buffer,bufferLength,fp);
	    printf("\t%s\n",buffer);
	}

	}

        fclose(fp);
    }




    printf("1.Add new habit.\n2.Register daily report.\n3.See current progress details.\n4.See current habits.\n5.Remove Habit\n6.Exit\n");

    while(selectionMain != 6){




        printf("\nSelect an option to continue: ");
        scanf("%d",&selectionMain);

        while(selectionMain > 6 || selectionMain < 1){
        while ( getchar() != '\n' );
        printf("Invalid entry. Please try again.\n");
        scanf("%d",&selectionMain);
        }

        switch(selectionMain){

            case 1:
                add_habit();
                // Add habit function.
                break;
            case 2:
                list_habits();
                printf("You can enter 0 to exit to main menu.");
                register_report();
                // get progress data function.
                break;
            case 3:
                show_detailed_report();
                // calculate details function.
                break;
            case 4:
                list_habits();
                break;
            case 5:
                list_habits();
                printf("\nPlease enter the index of the habit you want to remove.");
                scanf("%d",&entry);
                remove_habit(entry);
                printf("Habit removed from the list successfully.\n");
                break;
            case 6:
                printf("Exiting...");
                break;
            default:
                while ( getchar() != '\n' );
                printf("Invalid entry. Please try again.");
                break;
        }

                //fclose(fp2);



    }

    return 0;
}
/*

Simply removes a habit from the habit list.

This function removes the related line from both the habit_names.txt and habit_data.txt to remove a habit from its database.

The functionality is; the function loops through the lines of the txt files, storing them in an array, but when it comes to the line which is wished to be removed,
it skips that line and at the end array is filled with the datas of the habits left after one is removed.

*/

void remove_habit(int entry){

    FILE *fpDescriptions;
    FILE *fpData;

    fpDescriptions = fopen("habit_names.txt","r+");
    fpData = fopen("habit_data.txt","r");


    int habit_counter = 0;
    char chr;

// Number of habits is counted here.

    while (chr != EOF){
        //Count whenever new line is encountered
        if (chr == '\n'){
            habit_counter += 1;
        }
        //take next character from file.
        chr = getc(fpDescriptions);
    }

    rewind(fpDescriptions); // After the counting, we must rewind the cursor to the beggining of the txt file.

    int bufferLength = 64;
    char temp_habits_array[habit_counter][bufferLength]; // Array for storing habit names.
    char temp_data_array[habit_counter][bufferLength];  // Array for storing habit data.
    char garbage1[32]; // temp storage to skip through the elements which is wanted to be removed.
    char garbage2[32];
    int i=0;
    int k=0;


    for(i=0;i<habit_counter;i++){

        if(i == entry-1){ // if the iteration is on the line which is to be removed, it stores them in the garbage arrays, iterating over the line.
            fgets(garbage1,bufferLength,fpDescriptions);
            fgets(garbage2,bufferLength,fpData);
        }else{ // Else, it stores the habits left to rewrite them on the txts.
            fgets(temp_habits_array[k],bufferLength,fpDescriptions);
            fgets(temp_data_array[k],bufferLength,fpData);
            k++;
        }
    }


    fclose(fpDescriptions);
    fclose(fpData);

    fpDescriptions = fopen("habit_names.txt","w");
    fpData = fopen("habit_data.txt","w");

    // The habit datas stored in the arrays are rewritten to the txt files in the loop below.
    for(i=0;i<habit_counter-1;i++){
        fprintf(fpDescriptions,"%s",temp_habits_array[i]);
        fprintf(fpData,"%s",temp_data_array[i]);
    }

    fclose(fpDescriptions);
    fclose(fpData);

}
/*
This function gives a report of the habit progresses of the user.

The data given is; total days, succeed days, failed days, rights to skip, success percentage.

Basically reads data from habit_data.txt and process them to find the percentage etc.
*/

void show_detailed_report(){

    FILE *fpDescriptions;
    FILE *fpData;

    fpDescriptions = fopen("habit_names.txt","a+");
    fpData = fopen("habit_data.txt","a+");

    int bufferLength = 64;
    char buffer[bufferLength];

    char chr;
    int habit_counter = 0;
    int i;

    // Number of lines (habits) are counted.
    while (chr != EOF){
        //Count whenever new line is encountered
        if (chr == '\n'){
            habit_counter += 1;
        }
        //take next character from file.
        chr = getc(fpDescriptions);
    }

    fseek(fpDescriptions,0,SEEK_SET);

    int total_days;
    int succeed_days;
    int fail_days;



    for(i=0;i<habit_counter;i++){

        fgets(buffer, bufferLength, fpDescriptions);
        printf("%s\n",buffer);

        fscanf(fpData,"%d %d %d\n",&total_days,&succeed_days,&fail_days); // The data is read from the txt and assigned into variables.

        float succeed_fl = succeed_days;
        float total_fl = total_days;

        if(total_days==0){ // If there is no progress on a habit, the program crashes as it tries to calculate the percentage which causes to calculate 0/0.
            total_fl = 1; // To prevent errors, I set the denominator 1 so it doesn't crash.
        }

        printf("\tCurrent progress:\n\tTotal Days:%d\n\tSuccessful Days:%d\n\tFailed Days:%d\n\tRights to Skip Left:%d\n\tSuccess Rate: %%%.1f\n\n\n", total_days, succeed_days, fail_days,8-fail_days,(succeed_fl/total_fl)*100);

    }

}
/*
This function gets the progress input from the user.

Asks whether he failed the habit today or not.
*/
void register_report(){

    FILE *fp2;
        char chr2;
        fp2 = fopen("habit_names.txt","r");

        int num_of_habits = 0;

        while (chr2 != EOF){
            //Count whenever new line is encountered
            if (chr2 == '\n'){
                num_of_habits += 1;
            }
            //take next character from file.
            chr2 = getc(fp2);
        }

    fclose(fp2);


    FILE *fp;

    fp = fopen("habit_data.txt","r+");
    if(fp == NULL){
        printf("No habits are present.\n");
        return;
    }

    int habit_id;
    printf("\nPlease enter habit id to register daily report: "); // Gets the id of the habit.
    scanf("%d",&habit_id);
    while ( getchar() != '\n' );
    printf("habit id: %d   numofhabits: %d",habit_id,num_of_habits);
    if(habit_id != 0){
    while(habit_id > num_of_habits || habit_id < 1){
        while ( getchar() != '\n' );
        printf("Entry out of range. Please try again.\n");
        scanf("%d",&habit_id);
    }

    int counter = 0;
    int i=0;
    char chr;
    char daily_entry;

    int total_days;
    int succeed_days;
    int fail_days;
    int line_position;
    int bufferLength = 64;
    char buffer[bufferLength];
    for(i=0;i<habit_id;i++){
        if(i == habit_id-1){
            line_position = ftell(fp);
        }
        fscanf(fp,"%d %d %d\n",&total_days,&succeed_days,&fail_days); // Loops through the lines of the habit_data.txt and gets the related line.

    }

    printf("Have you done your habit today? (y/n) ");
    scanf("%c",&daily_entry); // Gets entry


    while(daily_entry != 'y' && daily_entry != 'n'){
        while ( getchar() != '\n' );
        printf("Invalid entry. Please type y for yes and type n for no.\n");
        printf("Have you done your habit today? (y/n) ");
        scanf("%c",&daily_entry);
    }

    if(daily_entry == 'y'){
        // If the answer is yes, then succeeded days increase by one, as well as the number of total days.
        total_days++;
        succeed_days++;
        if(succeed_days >= 23){
                // If the user completes a process of one month with less than 8 misses, he completes the habit and gets a badge of honor.
                //The habit is removed from the list after it is completed.
            printf("Congratulations!! You have mastered this habit. From now on, you are not bound of giving a report about it every single day!\n");
            printf("This habit is now removed, and will be showed as a badge of honor on the interface screen permanently!.");
            FILE *fp;
            fp = fopen("habit_names.txt","a+");
            for(i=0;i<habit_id;i++){
                fgets(buffer,bufferLength,fp);
            }
            fclose(fp);
            fp = fopen("badges.txt","a+");
            fprintf(fp,"COMPLETED: %s",buffer); // The completed habit is recorded name in the badges.txt
            remove_habit(habit_id);
        }
    }else if(daily_entry == 'n'){
        if(fail_days>=7){
            printf("With today's entry, your total of failed days become 8.\nYou have failed this habit, therefore your progress is reset.\nGood luck next time!\n");
            total_days = -1; // They are -1 instead of 0 because total_days and fail_days
            fail_days = -1; // get incremented below, yeah i know it's a sloppy hotfix lol.
            succeed_days = 0;
        }
        total_days++;
        fail_days++;
    }else printf("Error. Please report the situation to the developer.\n");

    // After the user registers a daily input, the current progress is shown on the screen.
    fseek(fp,line_position,SEEK_SET);
    fprintf(fp,"%d  %d  %d  ",total_days,succeed_days,fail_days);
    fclose(fp);
    float succeed_fl = succeed_days;
    float total_fl = total_days;

    if(total_days==0){ // If there is no progress on a habit, the program crashes as it tries to calculate the percentage which causes to calculate 0/0.
        total_fl = 1; // To prevent errors, I set the denominator 1 so it doesn't crash.
    }

    printf("\tCurrent progress:\n\tTotal Days:%d\n\tSuccessful Days:%d\n\tFailed Days:%d\n\tRights to Skip Left:%d\n\tSuccess Rate: %%%.1f\n", total_days, succeed_days, fail_days,8-fail_days,(succeed_fl/total_fl)*100);
    printf("\n\nThanks for your daily registerations.\n");

}else{
    printf("Exiting...");
}

}
/*
This function adds a new habit to the list, by writing the habit name in the habit_names.txt and
the progress stats(which is 0 0 0 for a new habit) into the habit_data.txt in parallel lines (same line number in both files).
*/
void add_habit(){

    FILE *fpDescriptions;
    FILE *fpData;

    fpDescriptions = fopen("habit_names.txt","a+");

    char chr;
    int habit_counter = 0;

    // Counting the number of lines/habits.
    while (chr != EOF){
        //Count whenever new line is encountered
        if (chr == '\n'){
            habit_counter += 1;
        }
        //take next character from file.
        chr = getc(fpDescriptions);
    }

    int habit_id = habit_counter + 1; // since the counter is started from zero, we increment it by one to get the correct id.

    printf("Currently there are %d habits in the file.\n\n",habit_counter);

    char habit_description[128];
    printf("Please enter a brief description for your new habit:\n");
    while ( getchar() != '\n' );
    scanf("%[^\n]s",habit_description);

    printf("Your new habit is: %s",habit_description);
    fprintf(fpDescriptions,"%s",habit_description);
    fprintf(fpDescriptions,"\n");


    fclose(fpDescriptions);

    fpData = fopen("habit_data.txt","a+");

    int total_days = 0;
    int days_succeed = 0;
    int days_failed = 0;

    fprintf(fpDescriptions,"%d  ",total_days);
    fprintf(fpDescriptions,"%d  ",days_succeed);
    fprintf(fpDescriptions,"%d  ",days_failed);
    fprintf(fpDescriptions,"\n");



    fclose(fpData);

}
/*
This function just reads the habit_names.txt line by line and adding indexes in front of them, creating a list on the screen.
*/
void list_habits(){

    FILE *fp;
    fp = fopen("habit_names.txt","r+");

    int i = 1;

    if(fp == NULL){ // checks whether the habit_names.txt file is exits or not.

        printf("\n\nNo habits present yet.");

    }else{

        printf("\n\nCurrent Habits:\n");

        int bufferLength = 255;
        char buffer[bufferLength];

        while(fgets(buffer, bufferLength, fp)){
            printf("%d. ",i);
            printf("%s", buffer);
            i++;
        }

    }
    fclose(fp);
}

