/***************************************************
 *                                                 *
 * file: among_us.c                                *
 *                                                 *
 * @Author  Antonios Peris                         *
 * @Version 20-10-2020                             *
 * @email   csdp1196@csd.uoc.gr                    *
 *                                                 *
 * @brief   Implementation of among_us.h           *
 *                                                 *
 ***************************************************
 */

#include "among_us.h"

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
    players_head = NULL;
    tasks_head =(struct Head_GL*)malloc(sizeof(struct Head_GL));
    tasks_head->tasks_count[0] = 0;
    tasks_head ->tasks_count[1] = 0;
    tasks_head -> tasks_count[2] = 0;
    tasks_head -> head = (struct Tasks*)malloc(sizeof(struct Tasks)); //Phantom task
    tasks_head->head = NULL;
    tasks_stack =(struct Head_Completed_Task_Stack*)malloc(sizeof(struct Head_Completed_Task_Stack));
    tasks_stack -> head = (struct Tasks*)malloc(sizeof(struct Tasks));
    tasks_stack ->head = NULL;
    tasks_stack->count=0;
    return 1;
}

/**
 * @brief Register player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid,int is_alien) {
    struct Players *new;
    struct Tasks *sentinel;
    
    new = (struct Players*)malloc(sizeof(struct Players)); 
    new -> pid = pid;
    new -> is_alien = is_alien;
    if(is_alien == 1){
       new -> evidence = 1;
    }
    else
    {
       new -> evidence = 0;
    }
    sentinel = (struct Tasks*)malloc(sizeof(struct Tasks)); 
    sentinel -> difficulty = -1;
    sentinel -> tid = -1;
    sentinel -> next = NULL;
    new -> tasks_sentinel = sentinel;
    new -> tasks_head = new -> tasks_sentinel;
    new -> next = players_head;
    new -> prev = NULL;
    if(players_head){
        players_head -> prev = new;
    }
    players_head = new;
    

    print_players();
    
    return 1;
}

/**
 * @brief Insert task in the general task list
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid,int difficulty) {
    struct Tasks *newTask, *prev, *temp;
    
    newTask = (struct Tasks*)malloc(sizeof(struct Tasks)); 
    newTask -> tid = tid;
    newTask -> difficulty = difficulty;
    newTask->next=NULL;
    
    if(!tasks_head->head){
        tasks_head->head=newTask;
        tasks_head->tasks_count[difficulty-1]++;
        return print_tasks();
    }

    if(tasks_head->head->difficulty > difficulty){
        newTask->next=tasks_head->head;
        tasks_head->head=newTask;
        tasks_head->tasks_count[difficulty-1]++;
        print_tasks();
        return 1;
    }

    temp=tasks_head->head;
    prev=NULL;
    
    while((temp) && (temp->difficulty!=difficulty)){
        prev=temp;
        temp=temp->next;
    }

    if(temp){
        if(prev){
            prev->next=newTask;
            newTask->next=temp; 
        }
        else{
            newTask->next = tasks_head->head;
            tasks_head->head = newTask;
        }
        
    }else{
        if(prev->difficulty<difficulty){
            prev->next=newTask;
        }else{
            temp=tasks_head->head;
            
            while(temp->difficulty!=difficulty-1){
                prev=temp;
                temp=temp->next;
            }
            prev->next=newTask;
            newTask->next=temp;
        }
    }
    tasks_head->tasks_count[difficulty-1]++;
    print_tasks();
    

    return 1;
}


/**
 * @brief Distribute tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() {
    struct Tasks* TaskToGo,*list,*temp,*prev; 
    struct Players* player = players_head;
    list = tasks_head->head;
    int i = 1;
    int a=1;
    int count;
    prev = NULL;
    while (player -> next)
    {
        a++;
        player = player->next;
    }
    player = players_head;
    
    while(list){
        TaskToGo = (struct Tasks*)malloc(sizeof(struct Tasks));
        TaskToGo -> tid = list -> tid;
        TaskToGo -> difficulty = list -> difficulty;
        count = i%a;
        int j=0;
        while(j<count){
            if(player->next){
                player -> prev = player;
                player = player -> next;
            }
            j++;
        }
        while ((player->next!=NULL)&&player->is_alien)
        {
            player = player->next;
        }
        if(player->is_alien){
            player = players_head;
            i = 1;
            while (player->is_alien)
            {
                player->prev = player;
                player = player->next;
            }
            
        }
        if(player ->tasks_head == player ->tasks_sentinel){ //<------case of the player task list being empty
            TaskToGo->next = player->tasks_head;
            player ->tasks_head = TaskToGo;
        }
        else{
            if(player->tasks_head->difficulty>TaskToGo->difficulty){ // <-------case of the first player task being more difficult than the task that's inserted.
                TaskToGo->next = player->tasks_head;
                player ->tasks_head = TaskToGo;
            }
            else{
                temp = player->tasks_head;
                while((temp->next!=NULL) && temp->difficulty!=TaskToGo->difficulty){ //<-- try to find a node with the same difficulty as the node that's inserted
                    prev = temp;
                    temp=temp->next;
                }
                if(temp){     //if you found it
                    if(prev){ //if it's not the first member on the task list
                        prev->next = TaskToGo;
                        TaskToGo->next = temp;
                    }
                    else{
                        TaskToGo->next = player->tasks_head;
                        player->tasks_head = TaskToGo;
                    }
                }
                else{ //if there is no node with this difficulty
                    if(prev->difficulty<TaskToGo->difficulty){
                        prev->next=TaskToGo;
                        TaskToGo->next = temp;
                    }else{
                        temp=player->tasks_head;
            
                        while((temp->next!=NULL) && temp->difficulty!=TaskToGo->difficulty-1){
                                prev=temp;
                                temp=temp->next;
                        }
                        prev->next=TaskToGo;
                        TaskToGo->next=temp;
                    }
                }
            }
        }
        player = players_head;
        list = list-> next;
        i++;
    }

    print_double_list();
    
    return 1;
}

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param difficulty The task's difficuly
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int difficulty) {
    struct Players* player = players_head;
    struct Tasks* task, *taskPrev, *temp, *retur;
    taskPrev = NULL;
    int i = 1;
    retur=(struct Tasks*)malloc(sizeof(struct Tasks));

    while ((player)&&(player -> pid  != pid))
    {
        player = player -> next;
        i++;
        
    }
    while(player->is_alien==1){
            player=player->next;
            i++;
    }
    if(player->tasks_head == player->tasks_sentinel){
        return 1;
    }
    if(player->tasks_head -> difficulty == difficulty){
        temp = player->tasks_head;
        player->tasks_head = player->tasks_head->next;
        retur->tid = temp->tid;
        retur->difficulty=temp->difficulty;
        free(temp);
    }
    else{
        task = player -> tasks_head;
        while ((task!=player->tasks_sentinel)&&(task -> difficulty != difficulty))
        {
            taskPrev = task;
            task = task -> next;
        }
        if(task != player->tasks_sentinel){
            taskPrev -> next = task->next;
            retur->tid = task->tid;
            retur->difficulty=task->difficulty;
            free(task);
        }
        else{
            if(player->tasks_head->difficulty>difficulty){
                temp = player->tasks_head;
                player->tasks_head = player->tasks_head->next;
                retur->tid = temp->tid;
                retur->difficulty=temp->difficulty;
                free(temp);  
            }
            else{
                temp = player->tasks_head;
                taskPrev = NULL;
                while((temp!=player->tasks_sentinel)&&(temp->difficulty!=difficulty+1)){
                    taskPrev = temp;
                    temp = temp->next;
                }
                if(temp == player->tasks_sentinel){
                    task = player->tasks_head;
                    player->tasks_head = player->tasks_head->next;
                    retur->tid = task->tid;
                    retur->difficulty=task->difficulty;
                    free(task);
                }
                else{
                    taskPrev->next=temp->next;
                    retur->tid = temp->tid;
                    retur->difficulty=temp->difficulty;
                    free(temp);
                }
                
            }

        }
    }
    retur->next = tasks_stack->head;
    tasks_stack->head = retur;
    
    tasks_stack->count++;
    
    print_double_list();

    
    
    return 1;
}

/**
 * @brief Eject Player
 * 
 * @param pid The ejected player's id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid) {
    struct Players* player, *player_temp, *player_min;
    player = players_head;
    struct Tasks* task, *task_min, *task_temp, *task_prev;
    //Find the player with player->pid = pid, delete him and save his tasks.
    while(player -> pid != pid){
        player = player -> next;
        if(!player){
            perror("pid doesn't exist");
            return 0;
        }
    }  
    task = player -> tasks_head;
    if(player->next == NULL){
        player->prev->next = NULL;
    }
    else if(player->prev == NULL){
        players_head = players_head->next;
    }
    else{
        player->prev->next = player->next;
        player->next->prev = player->prev;
    }
    free(player);
    //Find the player with the minimum amount of tasks
    player_min = players_head;
    int count = 1;
    task_temp=player_min->tasks_head;
    while(player_min->is_alien){
        player_min=player_min->next;
    }
    while(task_temp!=player_min->tasks_sentinel){
        count++;
        task_temp=task_temp->next;
    }
    player_temp = player_min;
    task_temp= player_temp ->tasks_head;
    task_prev = NULL;
    player_min=player_min->next;
    while (player_min != NULL)
    {
        while((player_min) && (player_min ->is_alien == 1)){
            player_min = player_min -> next;
        }
        if(player_min){
            int count2 = 1;
            task_min = player_min ->tasks_head;
            task_temp = player_min -> tasks_head;
            while (task_min != player_min -> tasks_sentinel)
            {
                count2++;
                task_min = task_min -> next;
            }
            if(count > count2){
                count = count2;
                player_temp = player_min;
                task_temp= player_temp ->tasks_head;
                task_prev = NULL;
            }
            player_min = player_min -> next;
        }
        task_temp=player_temp->tasks_head;
        
    }
    //pass the tasks to the player with the minimum amount of tasks.
    while(task->next != NULL){
        if(player_temp->tasks_head == player_temp->tasks_sentinel){
            task->next=player_temp->tasks_head; 
            player_temp->tasks_head = task;
        }
        else{
            if(task->difficulty<player_temp->tasks_head->difficulty){

                task->next = player_temp->tasks_head;
                player_temp->tasks_head = task;
            }
            else{
                while((task_temp!=player_temp->tasks_sentinel) && (task_temp->difficulty != task->difficulty)){
                    task_prev=task_temp;
                    task_temp=task_temp->next;
                }
                if(task_temp != player_temp->tasks_sentinel){
                    task_prev->next = task;
                    task->next = task_temp;
                }
                else{
                    if(task_prev->difficulty<task->difficulty){
                        task_prev->next=task;
                        task->next=task_temp;
                    }
                    else{
                        task_temp=player_temp->tasks_head;
                        task_prev= NULL;
                        while((task_temp != player_temp->tasks_sentinel) && (task_temp->difficulty != task->difficulty+1)){
                            task_prev = task_temp;
                            task_temp = task_temp->next;
                        }
                        task_prev->next = task;
                        task->next = task_temp;
                    }
                }
            }
        }
        task_prev = NULL;
        task_temp = player_temp->tasks_head;
        task = task->next;
        }

        //print_double_list();
    
    
    return 1;
}

/**
 * @brief Witness Eject Player
 *
 * @param pid_a The alien's pid
 * 
 * @param pid The crewmate's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid, int pid_a, int number_of_witnesses){

        eject_player(pid);

        struct Players* player,*alien;
        struct Tasks* task;

        alien = players_head;
        while(alien -> is_alien != 1){
            alien -> prev = alien;
            alien = alien ->next; 
        }
        alien -> evidence += number_of_witnesses;

        player = players_head;
        while(player != NULL){
            printf("<Player%d, %d> = ",player -> pid, player ->evidence);
            task = player -> tasks_head;
            while(task != player ->tasks_sentinel){
                printf("<%d,%d>,",task ->tid,task->difficulty);
                task = task ->next;
            }
            printf("\n");
        }
        printf("DONE");
    return 1;
}


/**
 * @brief Sabbotage
 *
 * @param pid The player's id
 *
 * @param number_of_tasks The number of tasks to be popped
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabbotage(int pid, int number_of_tasks) {
    struct Tasks* task, *rem, *prev;
    struct Players* player = players_head;
    int i = 0;
    int j = 0;
    //Find player----------
    if(!players_head){
        return 0;
    }
    while(player -> pid != pid){
            player = player -> next;
            if(!player){
                return 0;
            }
        }
    if(player -> is_alien == 0){
        while(j < number_of_tasks/2){
            player = player ->prev;
            j++;
            if(player==players_head){
                j = number_of_tasks;
            }
        }
        while((player) &&(player->is_alien)){
            player = player->next;
                
        }
    }
    else{
        while((player->next != NULL)&&(player -> is_alien)){
            player = player -> next;
        }
    }
    if(player->next == NULL){
        player=players_head;
        while(player->is_alien){
            player = player->next;
        }
    }
    //End find player------
    //Insert tasks---------
    while(i<number_of_tasks){
        rem = (struct Tasks*)malloc(sizeof(struct Tasks));
        if(player->tasks_head == player->tasks_sentinel){
            if(tasks_stack->count==0){
                rem=NULL;
            }
            else{
                rem = tasks_stack->head;
                tasks_stack->head = tasks_stack->head->next;
                tasks_stack->count = tasks_stack->count-1;
            }
            rem->next = player->tasks_head;
            player->tasks_head = rem;
        }
        else if(rem->difficulty<player->tasks_head->difficulty){
            if(tasks_stack->count==0){
                rem=NULL;
            }
            else{
                rem = tasks_stack->head;
                tasks_stack->head = tasks_stack->head->next;
                tasks_stack->count = tasks_stack->count-1;
            }
            rem->next = player->tasks_head;
            player->tasks_head = rem;
        }
        else{
            task = player->tasks_head;
            prev = NULL;
            while((task!=player->tasks_sentinel)&&(rem->difficulty!=task->difficulty)){
                prev = task;
                task = task -> next;
            }
            if(task!=player->tasks_sentinel){

                if(tasks_stack->count==0){
                    rem=NULL;
                }
                else{
                    rem = tasks_stack->head;
                    tasks_stack->head = tasks_stack->head->next;
                    tasks_stack->count = tasks_stack->count-1;
                }
                prev->next = rem;
                rem -> next = task;
            }
            else{
                task = player->tasks_head;
                prev = NULL;
                while((task!=player->tasks_sentinel) && (task->difficulty!=rem->difficulty+1)){
                    prev=task;
                    task = task->next;
                }
                if(tasks_stack->count==0){
                    rem=NULL;
                }
                else{
                    rem = tasks_stack->head;
                    tasks_stack->head = tasks_stack->head->next;
                    tasks_stack->count = tasks_stack->count-1;
                }
                prev->next = rem;
                rem->next = task;
            }
        }
        i++;
        if(!tasks_stack->head){
            return 0;
        }
        player = player ->next;
        while((player)&&(player->is_alien)){
            player=player->next;
        }
        if(!player){
            player = players_head;
            while((player)&&(player->is_alien)){
                player=player->next;
            }
        }             
    }
    //End insert tasks------
    print_double_list();
    return 1;
}


/**
 * @brief Vote
 *
 * @param pid The player's id
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid, int vote_evidence) {
    struct Players* max_player, *player = players_head;
    struct Tasks* task;
    while (player -> pid != pid)
    {
        player -> prev = player;
        player = player -> next;
    }
    player -> evidence += vote_evidence;
    max_player = player;
    player = players_head;
    
    while(player != NULL){
        if(player -> evidence > max_player ->evidence){
            max_player = player;
        }
    }
    eject_player(max_player ->pid);

    player = players_head;
    while(player != NULL){
        printf("<Player%d, %d> = ",player -> pid, player ->evidence);
        task = player -> tasks_head;
        while(task != player ->tasks_sentinel){
            printf("<%d,%d>,",task ->tid,task->difficulty);
            task = task ->next;
        }
        printf("\n");
    }
    printf("DONE");
    
    return 1;
}


/**
 * @brief Give Away Work
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work() {
    struct Players* playerMin,*PlayerMax,*player = players_head;
    struct Tasks* task,*taskMin,*taskMax, *prev;
    int i=1;
    int j=1;
    int k = 1;
    int o = 1;
    task = player ->tasks_head;
    while(task != player ->tasks_sentinel){
        task = task -> next;
        i++;
        k++;
    }
    player = players_head;
    task = player -> tasks_head;
    while(1){
        while (player->is_alien == 1)
        {
            player = player->next;
            if(player->next == NULL){
                break;
            }
        }
        
        while(task != player ->tasks_sentinel){
            task = task -> next;
            j++;
        }
        if(j < i){
            playerMin = player;
            i = j;
        }
        if(j > k){
            PlayerMax = player;
            k = j;
        }
        player = player->next;
        if(player){
            task = player->tasks_head; 
        }
        o++;
        if(player->next == NULL){
            break;
        }
    }
    
    taskMax = PlayerMax ->tasks_head;
    taskMin = playerMin ->tasks_head;
    j = 0;
    int p;
    for(p = 0; p<k/2; p++){
        if(taskMax ->difficulty <= taskMin->difficulty){
            taskMax->next = taskMin;
            taskMin = taskMax;
        }
        else{
            prev = NULL;
            while(taskMax->difficulty > taskMin->difficulty){
                prev = taskMin;
                taskMin = taskMin->next;
            }
            prev->next = taskMax;
            taskMax->next = taskMin;
        }
        if(taskMax->next == NULL){
            print_double_list();
    
            return 1;
        }
        else{
            taskMax = taskMax->next;
        }
        
    }

    print_double_list();
    
    return 1;
}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate() {
    struct Players* player = players_head;
    struct Tasks* gl;
    gl = tasks_head->head;
    int aliens = 0;
    int players = 0;
    int total_players = 0;
    int tasks_num = 0;
    while(gl != NULL){
        tasks_num += 1;
        gl = gl->next;
    }
    while(player != NULL){
        if(player -> is_alien == 1){
            aliens += 1;
        }
        else{
            players += 1;
        }
        total_players += 1;
        player = player ->next;
    }
    if(aliens > players){
        printf("Aliens Win");
        printf("\nDONE\n");
    }
    else{
        if(aliens == 0){
            printf("Humans Win");
            printf("\nDONE\n");
        }
        else if(tasks_stack->count == tasks_num){
            printf("Humans Win");
            printf("\nDONE\n");
        }
    }
    return 1;
}

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
    struct Players* temp = players_head;
    printf("Players=");
    while (temp != NULL)
    {
        printf("<%d:%d>", temp -> pid, temp -> is_alien);
        temp = temp -> next;
    }
    printf("\nDONE\n");
    
    return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {
    struct Tasks* temp=tasks_head->head;
    printf("Tasks=");
    while (temp)
    {
        printf("<%d:%d>", temp-> tid, temp-> difficulty);
        temp = temp-> next;
    }
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Stack
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stack() {
    struct Head_Completed_Task_Stack* list;
    list = tasks_stack;
    printf("STACK_TASKS=");
    while(list ->head != NULL){
        printf("<%d,%d>",list ->head ->tid, list ->head ->difficulty);
        list->head = list->head->next;
    }
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Players & Task List
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_list() {
    struct Players* player = players_head;
    struct Tasks* task;
    while(player){
        task = player -> tasks_head;
        printf("Player= ");
        while(task != player -> tasks_sentinel){
            printf("<%d:%d>", task -> tid, task -> difficulty);
            task = task->next;
        }
        printf("\n");
        player = player -> next;
    }
    printf("\nDONE\n"); 

    return 1;
}


/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void) {
    return 1;
}
