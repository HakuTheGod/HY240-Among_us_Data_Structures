/***************************************************
 *                                                 *
 * file: among_us.c                                *
 *                                                 *
 * @Author  Skerdi Basha                           *
 * @Version 1-12-2020                              *
 * @email   sbash@csd.uoc.gr                       *
 *                                                 *
 * @brief   Implementation of among_us.h           *
 *                                                 *
 ***************************************************
 */

#include "among_us.h"

unsigned int primes_g[650] = { 
                                 179,    181,    191,    193,    197,    199,    211,    223,    227,    229, 
                                 233,    239,    241,    251,    257,    263,    269,    271,    277,    281, 
                                 283,    293,    307,    311,    313,    317,    331,    337,    347,    349, 
                                 353,    359,    367,    373,    379,    383,    389,    397,    401,    409, 
                                 419,    421,    431,    433,    439,    443,    449,    457,    461,    463, 
                                 467,    479,    487,    491,    499,    503,    509,    521,    523,    541, 
                                 547,    557,    563,    569,    571,    577,    587,    593,    599,    601, 
                                 607,    613,    617,    619,    631,    641,    643,    647,    653,    659, 
                                 661,    673,    677,    683,    691,    701,    709,    719,    727,    733, 
                                 739,    743,    751,    757,    761,    769,    773,    787,    797,    809, 
                                 811,    821,    823,    827,    829,    839,    853,    857,    859,    863, 
                                 877,    881,    883,    887,    907,    911,    919,    929,    937,    941, 
                                 947,    953,    967,    971,    977,    983,    991,    997,   1009,   1013, 
                                1019,   1021,   1031,   1033,   1039,   1049,   1051,   1061,   1063,   1069, 
                                1087,   1091,   1093,   1097,   1103,   1109,   1117,   1123,   1129,   1151, 
                                1153,   1163,   1171,   1181,   1187,   1193,   1201,   1213,   1217,   1223, 
                                1229,   1231,   1237,   1249,   1259,   1277,   1279,   1283,   1289,   1291, 
                                1297,   1301,   1303,   1307,   1319,   1321,   1327,   1361,   1367,   1373, 
                                1381,   1399,   1409,   1423,   1427,   1429,   1433,   1439,   1447,   1451, 
                                1453,   1459,   1471,   1481,   1483,   1487,   1489,   1493,   1499,   1511, 
                                1523,   1531,   1543,   1549,   1553,   1559,   1567,   1571,   1579,   1583, 
                                1597,   1601,   1607,   1609,   1613,   1619,   1621,   1627,   1637,   1657, 
                                1663,   1667,   1669,   1693,   1697,   1699,   1709,   1721,   1723,   1733, 
                                1741,   1747,   1753,   1759,   1777,   1783,   1787,   1789,   1801,   1811, 
                                1823,   1831,   1847,   1861,   1867,   1871,   1873,   1877,   1879,   1889, 
                                1901,   1907,   1913,   1931,   1933,   1949,   1951,   1973,   1979,   1987, 
                                1993,   1997,   1999,   2003,   2011,   2017,   2027,   2029,   2039,   2053, 
                                2063,   2069,   2081,   2083,   2087,   2089,   2099,   2111,   2113,   2129, 
                                2131,   2137,   2141,   2143,   2153,   2161,   2179,   2203,   2207,   2213, 
                                2221,   2237,   2239,   2243,   2251,   2267,   2269,   2273,   2281,   2287, 
                                2293,   2297,   2309,   2311,   2333,   2339,   2341,   2347,   2351,   2357, 
                                2371,   2377,   2381,   2383,   2389,   2393,   2399,   2411,   2417,   2423, 
                                2437,   2441,   2447,   2459,   2467,   2473,   2477,   2503,   2521,   2531, 
                                2539,   2543,   2549,   2551,   2557,   2579,   2591,   2593,   2609,   2617, 
                                2621,   2633,   2647,   2657,   2659,   2663,   2671,   2677,   2683,   2687, 
                                2689,   2693,   2699,   2707,   2711,   2713,   2719,   2729,   2731,   2741, 
                                2749,   2753,   2767,   2777,   2789,   2791,   2797,   2801,   2803,   2819, 
                                2833,   2837,   2843,   2851,   2857,   2861,   2879,   2887,   2897,   2903, 
                                2909,   2917,   2927,   2939,   2953,   2957,   2963,   2969,   2971,   2999, 
                                3001,   3011,   3019,   3023,   3037,   3041,   3049,   3061,   3067,   3079, 
                                3083,   3089,   3109,   3119,   3121,   3137,   3163,   3167,   3169,   3181, 
                                3187,   3191,   3203,   3209,   3217,   3221,   3229,   3251,   3253,   3257, 
                                3259,   3271,   3299,   3301,   3307,   3313,   3319,   3323,   3329,   3331, 
                                3343,   3347,   3359,   3361,   3371,   3373,   3389,   3391,   3407,   3413, 
                                3433,   3449,   3457,   3461,   3463,   3467,   3469,   3491,   3499,   3511, 
                                3517,   3527,   3529,   3533,   3539,   3541,   3547,   3557,   3559,   3571, 
                                3581,   3583,   3593,   3607,   3613,   3617,   3623,   3631,   3637,   3643, 
                                3659,   3671,   3673,   3677,   3691,   3697,   3701,   3709,   3719,   3727, 
                                3733,   3739,   3761,   3767,   3769,   3779,   3793,   3797,   3803,   3821, 
                                3823,   3833,   3847,   3851,   3853,   3863,   3877,   3881,   3889,   3907, 
                                3911,   3917,   3919,   3923,   3929,   3931,   3943,   3947,   3967,   3989, 
                                4001,   4003,   4007,   4013,   4019,   4021,   4027,   4049,   4051,   4057, 
                                4073,   4079,   4091,   4093,   4099,   4111,   4127,   4129,   4133,   4139, 
                                4153,   4157,   4159,   4177,   4201,   4211,   4217,   4219,   4229,   4231, 
                                4241,   4243,   4253,   4259,   4261,   4271,   4273,   4283,   4289,   4297, 
                                4327,   4337,   4339,   4349,   4357,   4363,   4373,   4391,   4397,   4409, 
                                4421,   4423,   4441,   4447,   4451,   4457,   4463,   4481,   4483,   4493, 
                                4507,   4513,   4517,   4519,   4523,   4547,   4549,   4561,   4567,   4583, 
                                4591,   4597,   4603,   4621,   4637,   4639,   4643,   4649,   4651,   4657, 
                                4663,   4673,   4679,   4691,   4703,   4721,   4723,   4729,   4733,   4751, 
                                4759,   4783,   4787,   4789,   4793,   4799,   4801,   4813,   4817,   4831, 
                                4861,   4871,   4877,   4889,   4903,   4909,   4919,   4931,   4933,   4937, 
                                4943,   4951,   4957,   4967,   4969,   4973,   4987,   4993,   4999,   5003, 
                                5009,   5011,   5021,   5023,   5039,   5051,   5059,   5077,   5081,   5087, 
                                5099,   5101,   5107,   5113,   5119,   5147,   5153,   5167,   5171,   5179, 
                            };


/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
    sentinel = (struct Player*)malloc(sizeof(struct Player));
    sentinel->pid = -1;
    sentinel->is_alien = 0;
    sentinel->lc = players_tree;
    sentinel->rc = players_tree;
    sentinel->evidence = 0;
    sentinel->parrent = NULL;
    sentinel->tasks = NULL;
    players_tree = sentinel;
    players_tree->parrent = sentinel;
    general_tasks_ht =(struct General_Tasks_HT*)malloc(sizeof(struct General_Tasks_HT));
    general_tasks_ht->count = 0;
    general_tasks_ht->tasks = malloc(sizeof(struct HT_Task*) * max_tasks_g);
    int count = 0;
    for(count = 0; count<max_tasks_g; count++){
        general_tasks_ht->tasks[count] = NULL;
    }
    counter = 0;
    found = 0;
    newPlayer = NULL;
    taskA = NULL;
    completed_tasks_pq = (struct Completed_Tasks_PQ*)malloc(sizeof(struct Completed_Tasks_PQ));
    completed_tasks_pq->size = 0;
    completed_tasks_pq->tasks = malloc(sizeof(struct HT_Task*) * max_tasks_g);
    alien = sentinel;
    return 1;
}

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien) {
    struct Player* newPlayer, *temp;
    newPlayer = (struct Player*)malloc(sizeof(struct Player));
    newPlayer->pid = pid;
    newPlayer->is_alien = is_alien;
    newPlayer->tasks = NULL;
    if(is_alien == 0){
        newPlayer->evidence = 0;
    }
    else
    {
        newPlayer->evidence = 1;
    }
    if(players_tree == sentinel){
        newPlayer->lc = players_tree;
        newPlayer->rc = players_tree;
        newPlayer->parrent = players_tree;
        players_tree = newPlayer;
    }
    else{
        temp = players_tree;
        while((temp->lc != sentinel) || (temp->rc != sentinel)){
            if(newPlayer->pid == temp->pid){
                print_players();
                return 0;
            }
            if(temp->lc == sentinel && newPlayer->pid < temp->pid){
                newPlayer->parrent = temp;
                newPlayer->lc = sentinel;
                newPlayer->rc = sentinel;
                temp->lc = newPlayer;
                print_players();
                return 1;
            }
            if(temp->rc == sentinel && newPlayer->pid > temp->pid){
                newPlayer->parrent = temp;
                newPlayer->lc = sentinel;
                newPlayer->rc = sentinel;
                temp->rc = newPlayer;
                print_players();
                return 1;
            }
            if(newPlayer->pid < temp->pid){
                temp = temp->lc;
            }
            else{
                temp = temp->rc; 
            }
        }
        if(newPlayer->pid < temp->pid){
            newPlayer->parrent = temp;
            newPlayer->lc = sentinel;
            newPlayer->rc = sentinel;
            temp->lc = newPlayer;
        }
        else{
            newPlayer->parrent = temp;
            newPlayer->lc = sentinel;
            newPlayer->rc = sentinel;
            temp->rc = newPlayer;
        }
    }
    print_players();
    return 1;
}

/**
 * @brief Insert Task in the general task hash table
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid, int difficulty) {
    struct HT_Task* task;
    int key;
    task = (struct HT_Task*)malloc(sizeof(struct HT_Task));
    task->tid = tid;
    task->difficulty = difficulty;
    key = hashFunction(tid)%max_tasks_g;
    task->next = general_tasks_ht->tasks[key];
    general_tasks_ht->tasks[key] = task;
    general_tasks_ht->count++;
    print_tasks();
    return 1;
}

/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() {
    struct HT_Task* tasks;
    struct Player* player;
    struct Task* pt, *taskP;
    player = players_tree;
    int a = 0;
    int b=1;
    int i;
    int num;
    num = countNodes(player);
    player = players_tree;
    for(i = 0; i<max_tasks_g; i++){
        tasks = general_tasks_ht->tasks[i];
        while(tasks == NULL){
            i++;
            tasks = general_tasks_ht->tasks[i];
        }
        while(tasks){
            pt = (struct Task*)malloc(sizeof(struct Task));
            pt->tid = tasks->tid;
            pt->difficulty = tasks->difficulty;
            pt->lcnt = 0;
            a = b%num;
            counter = 0;
            found = 0;
            findNthInOrder(player, a);
            while(newPlayer->is_alien){
                if(((newPlayer->lc == sentinel) && (newPlayer->rc == sentinel)) || ((newPlayer->lc == sentinel) && (newPlayer->rc->is_alien == 1)) || ((newPlayer->lc->is_alien) && (newPlayer->rc == sentinel))){
                    newPlayer = newPlayer->parrent;
                }
                else if(newPlayer->lc->is_alien == 0){
                    newPlayer = newPlayer->lc;
                }
                else if(newPlayer->rc->is_alien == 0){
                    newPlayer = newPlayer->rc;
                }
                else{
                    if((newPlayer->lc->lc != sentinel) || (newPlayer->lc->rc != sentinel)){
                        newPlayer = newPlayer->lc;
                    }
                    else if((newPlayer->rc->lc != sentinel) || (newPlayer->rc->rc != sentinel)){
                        newPlayer = newPlayer->rc;
                    }
                }
            }
            taskP = newPlayer->tasks;
            if(newPlayer->tasks == NULL){
                pt->lc = newPlayer->tasks;
                pt->rc = newPlayer->tasks;
                newPlayer->tasks = pt;
            }
            else if((newPlayer->tasks) && ((newPlayer->tasks->lc == NULL) && (newPlayer->tasks->rc == NULL))){
                if(pt->tid < taskP->tid){
                    pt->lc = NULL;
                    pt->rc = NULL;
                    taskP->lc = pt;
                }
                else{
                    pt->lc = NULL;
                    pt->rc = NULL;
                    taskP->rc = pt;
                }
            }
            else{
                while((taskP->lc != NULL) || (taskP->rc != NULL)){
                    if((taskP->lc == NULL) && (pt->tid < taskP->tid)){
                        pt->lc = NULL;
                        pt->rc = NULL;
                        taskP->lc = pt;
                        break;
                    }
                    else if((taskP->rc == NULL) && (pt->tid > taskP->tid)){
                        pt->lc = NULL;
                        pt->rc = NULL;
                        taskP->rc = pt;
                        break;
                    }
                    else{
                        if(pt->tid < taskP->tid){
                            taskP = taskP->lc;
                        }
                        else{
                            taskP = taskP->rc;
                        }
                    }
                }
                if(pt->tid < taskP->tid){
                    pt->lc = NULL;
                    pt->rc = NULL;
                    taskP->lc = pt;
                }
                else{
                    pt->lc = NULL;
                    pt->rc = NULL;
                    taskP->rc = pt;
                }
            }
            updateLcnt(taskP);
            tasks = tasks->next;
            b++;
            player = players_tree;
            newPlayer = NULL;
        }

    }
    print_double_tree();
    return 1;
}

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param tid The task's tid
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int tid) {
    struct Player* player;
    struct Task* pt;
    newPlayer = NULL;
    player = players_tree;
    findPlayer(player, pid);
    pt = newPlayer->tasks;
    taskA = pt;
    if(taskA != NULL){
         printf("\n %d \n", taskA->tid);
    }
   
    if(pt == NULL){
        print_double_tree();
        return 1;
    }
    if(pt ->lc == NULL && pt ->rc == NULL){
        if(pt->tid == tid){
            //insertPQ(completed_tasks_pq->tasks, newPlayer->tasks);
            newPlayer->tasks = NULL;
            print_double_tree();
            return 1;
        }
    }
    if(pt->tid == tid && pt->lc == NULL && pt->rc != NULL){
        pt = newPlayer->tasks->rc;
        //insertPQ(completed_tasks_pq->tasks, newPlayer->tasks);
        newPlayer->tasks = pt;
        counter = 0;
        struct Task* p = newPlayer->tasks;
        updateLcnt(p);
        print_double_tree();
        return 1;
    }
    else if(pt->tid == tid && pt->lc != NULL && pt->rc == NULL){
        pt = newPlayer->tasks->lc;
        //insertPQ(completed_tasks_pq->tasks, newPlayer->tasks);
        newPlayer->tasks = pt;
        counter = 0;
        struct Task* p = newPlayer->tasks;
        updateLcnt(p);
        print_double_tree();
        return 1;
    }
    taskA = deleteInOrder(pt, tid);
    counter = 0;
    pt = newPlayer->tasks;
    updateLcnt(pt);
    print_double_tree();
    return 1;
}

/**
 * @brief Eject Player
 * 
 * @param pid_1 The ejected player's id
 *
 * @param pid_2 The crewmates id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid_1, int pid_2) {

    struct Player* player1;
    struct Task* taskP1, *taskP2;
    newPlayer = NULL;

    player1 = players_tree;

    findPlayer(player1, pid_1);

    taskP1 = newPlayer->tasks;

    deletePlayerInOrder(newPlayer, pid_1);

    player1 = players_tree;

    newPlayer = NULL;

    findPlayer(player1, pid_2);

    while(newPlayer->is_alien == 1){
        if((newPlayer->lc == sentinel && newPlayer->rc == sentinel) || (newPlayer->lc->is_alien == 1 && newPlayer->rc->is_alien == 1)){
            newPlayer = newPlayer->parrent;
        }
        else if(newPlayer->lc->is_alien == 0){
            newPlayer = newPlayer->lc;
        }
        else{
            newPlayer = newPlayer->rc;
        }
    }

    taskP2 = newPlayer->tasks;

    insertToTree(taskP1, taskP2);
    
    print_double_tree();
    return 1;
}

/**
 * @brief Witness Eject Player
 *
 * @param pid_1 The ejected player's id
 * 
 * @param pid_2 The crewmate's pid
 *
 * @param pid_a The alien's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses){
    struct Player* player1;
    struct Task* taskP1, *taskP2;
    newPlayer = NULL;

    player1 = players_tree;

    findPlayer(player1, pid_1);

    taskP1 = newPlayer->tasks;

    deletePlayerInOrder(newPlayer, pid_1);

    player1 = players_tree;

    newPlayer = NULL;

    findPlayer(player1, pid_2);

    while(newPlayer->is_alien == 1){
        if((newPlayer->lc == sentinel && newPlayer->rc == sentinel) || (newPlayer->lc->is_alien == 1 && newPlayer->rc->is_alien == 1)){
            newPlayer = newPlayer->parrent;
        }
        else if(newPlayer->lc->is_alien == 0){
            newPlayer = newPlayer->lc;
        }
        else{
            newPlayer = newPlayer->rc;
        }
    }

    taskP2 = newPlayer->tasks;

    insertToTree(taskP1, taskP2);

    newPlayer = NULL;
    player1 = players_tree;

    findPlayer(player1, pid_a);

    newPlayer->evidence += number_of_witnesses;
    
    print_double_treeEvidence();
    return 1;
    return 1;
}

/**
 * @brief Sabotage
 *
 * @param number_of_tasks The number of tasks to be sabotaged
 *
 * @param pid The player's id
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabotage(int number_of_tasks, int pid) {
    struct Task* retTask;
    struct HT_Task* t = &completed_tasks_pq->tasks[0];
    struct Player* player, *temp;
    int i = 0;
    player = players_tree;
    findPlayer(player,pid);
    while(i<number_of_tasks/2){
        temp = findInOrderPredecessor();
        i++;
    }
    i = 0;
    while(i<number_of_tasks/2){
        retTask = (struct Task*)malloc(sizeof(struct Task));
        retTask->tid = t->tid;
        retTask->difficulty = t->difficulty;
        retTask->lcnt = 0;
        newPlayer = temp;
        insertTask(retTask, newPlayer);
        deleteRoot(t,retTask);
        temp = findInOrderSucessor();
        i++;
    }
    print_double_tree();
    return 1;
}

/**
 * @brief Vote
 *
 * @param pid_1 The suspicious player's id
 *
 * @param pid_2 The crewmate's pid
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid_1, int pid_2, int vote_evidence) {
    struct Player* player;
    struct Task* task;
    player = players_tree;
    alien = sentinel;
    findPlayer(player, pid_1);
    newPlayer->evidence += vote_evidence;
    player = players_tree;
    findAlien(player);
    player = players_tree;
    findPlayer(player, pid_2);
    task = newPlayer->tasks;
    insertToTree(alien->tasks, task);
    deletePlayerInOrder(alien, alien->pid);
    print_double_treeEvidence();
    return 1;
}

/**
 * @brief Give Away Work
 *
 * @param pid_1 The existing crewmate's id
 *
 * @param pid_2 The new crewmate's pid
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work(int pid_1, int pid_2) {
    struct Player* Player2, *temp;
    struct Task* task;
    Player2 = (struct Player*)malloc(sizeof(struct Player));
    Player2->pid = pid_2;
    Player2->is_alien = 0;
    Player2->tasks = NULL;
    Player2->evidence = 0;
    if(players_tree == sentinel){
        Player2->lc = players_tree;
        Player2->rc = players_tree;
        Player2->parrent = players_tree;
        players_tree = Player2;
    }
    else{
        temp = players_tree;
        while((temp->lc != sentinel) || (temp->rc != sentinel)){
            if(Player2->pid == temp->pid){
                return 0;
            }
            if(temp->lc == sentinel && Player2->pid < temp->pid){
                Player2->parrent = temp;
                Player2->lc = sentinel;
                Player2->rc = sentinel;
                temp->lc = Player2;
                break;
            }
            if(temp->rc == sentinel && Player2->pid > temp->pid){
                Player2->parrent = temp;
                Player2->lc = sentinel;
                Player2->rc = sentinel;
                temp->rc = Player2;
                break;
            }
            if(Player2->pid < temp->pid){
                temp = temp->lc;
            }
            else{
                temp = temp->rc; 
            }
        }
        if(Player2->lc == sentinel && Player2->rc == sentinel){
            if(Player2->pid < temp->pid){
                Player2->parrent = temp;
                Player2->lc = sentinel;
                Player2->rc = sentinel;
                temp->lc = Player2;
            }
            else{
                Player2->parrent = temp;
                Player2->lc = sentinel;
                Player2->rc = sentinel;
                temp->rc = Player2;
            }
        }  
    }
    temp = players_tree;
    findPlayer(temp, pid_1);
    task = newPlayer->tasks;
    int p;
    p = findNumberOfTasks(task, 0);
    int i = 0;
    while(i < p/2){
        if(task == NULL){
            break;
        }
        if(task ->lc == NULL && task ->rc == NULL){
            newPlayer->tasks = NULL;
            insertTask(task, Player2);
        }
        if(task->lc == NULL && task->rc != NULL){
            newPlayer->tasks = newPlayer->tasks->rc;
            insertTask(task, Player2);
        }
        else if(task->lc != NULL && task->rc == NULL){
            newPlayer->tasks = newPlayer->tasks->lc;
            insertTask(task, Player2);
        }
        else{
            deleteInOrder(task, task->tid);
        }
        i++;
    }
    print_double_tree();
    return 1;
}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate() {
    struct Player* player = players_tree;
    counter = 0;
    found = 0;
    findNumberOfPlayers(player);
    player = players_tree;
    findNumberOfAliens(player);
    if(found == 0 || completed_tasks_pq->size == max_tasks_g){
        printf("\n Crewmates Win \n");
        printf("\n DONE \n");
        return 1;
    }
    if(found<counter){
        printf("\n Aliens Win \n");
        printf("\n DONE \n");
    }
    else if(found > counter){
        printf("\n Crewmates Win \n");
        printf("\n DONE \n");
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
    struct Player* curr;
    curr = players_tree;
    if (players_tree == NULL){
        return 1;
    }
    printf("Player = ");
    
    recur(curr);
    
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
    int i;

    for(i = 0; i < max_tasks_g; i++)
    {
        struct HT_Task *temp = general_tasks_ht->tasks[i];
        printf("chain[%d]:",i);
        while(temp)
        {
            printf("<%d,%d>",temp->tid, temp->difficulty);
            temp = temp->next;
        }
        printf("\n \n");
    }
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq() {
    struct HT_Task* task;
    printf("Completed Tasks =");
    int i;
    for (i = 0; i < completed_tasks_pq->size; ++i){
        task = &completed_tasks_pq->tasks[i];
        printf("<%d,%d>", task->tid, task->difficulty);
    }
    printf("\n DONE \b");
    
  
    return 1;
}

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree() {
    struct Player* curr;
    curr = players_tree;
    if (players_tree == NULL){
        return 1;
    }
    
    recurDoubleP(curr);
    printf("\n \n");
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

/**
 * @brief Print the players recursively
 *
 * @param root The player's tree root
 * 
 */
void recur(struct Player* root){
    if (root == sentinel){
          return; 
    }
     recur(root->lc); 
  
     printf("<%d,%d>", root->pid, root->is_alien);   
  
     recur(root->rc); 
}

/**
 * @brief Inserts the task tree of a player to another player's task tree
 *
 * @param taskP1 The root of the giving player's task tree
 *
 * @param taskP2 the root of the recieving player's task tree
 *
 */
void insertToTree(struct Task* taskP1, struct Task* taskP2){
    if(taskP1 == NULL){
        return;
    }
    struct Task* temp = (struct Task*)malloc(sizeof(struct Task));
    temp->tid = taskP1->tid;
    temp->difficulty = taskP1->difficulty;
    temp->lcnt = 0;

    if(taskP2 == NULL){
            temp->lc = NULL;
            temp->rc = NULL;
            taskP2 = temp;
        }
        else if((taskP2) && ((taskP2->lc == NULL) && (taskP2->rc == NULL))){
            if(temp->tid < taskP2->tid){
                temp->lc = NULL;
                temp->rc = NULL;
                taskP2->lc = temp;
            }
            else{
                temp->lc = NULL;
                temp->rc = NULL;
                taskP2->rc = temp;
            }
        }
        else{
            while((taskP2->lc != NULL) || (taskP2->rc != NULL)){
                if((taskP2->lc == NULL) && (temp->tid < taskP2->tid)){
                    temp->lc = NULL;
                    temp->rc = NULL;
                    taskP2->lc = temp;
                    break;
                }
                else if((taskP2->rc == NULL) && (temp->tid > taskP2->tid)){
                    temp->lc = NULL;
                    temp->rc = NULL;
                    taskP2->rc = temp;
                    break;
                }
                else{
                    if(temp->tid < taskP2->tid){
                        taskP2 = taskP2->lc;
                    }
                    else{
                        taskP2 = taskP2->rc;
                    }
                }
            }
            if(temp->tid < taskP2->tid){
                temp->lc = NULL;
                temp->rc = NULL;
                taskP2->lc = temp;
            }
            else{
                temp->lc = NULL;
                temp->rc = NULL;
                taskP2->rc = taskP1;
            }
        }
        updateLcnt(taskP2);
        if(taskP1->rc == NULL){
            insertToTree(taskP1->lc, taskP2);
        }
        else if(taskP1->lc == NULL){
            insertToTree(taskP1->rc, taskP2);
        }
        else{
            insertToTree(taskP1->lc, taskP2);
            insertToTree(taskP1->rc, taskP2);
        }

}

/**
 * @brief Hash function for the hash table
 *
 * @param tid The current task's tid
 *
 * @return the resault of the hash function
 */
int hashFunction(int tid){
    return(tid*primes_g[tid]%max_tid_g)%max_tasks_g;
}

/**
 * @brief counts the nodes of the player tree
 *
 * @param root The root of the player tree
 *
 * @return The number of the player nodes on success 
 *         0 on failure
 */
int countNodes(struct Player* root){
    if (root == NULL){
      return 0;
   }
   int result = 0;
   if ((root->lc != sentinel) || (root->rc != sentinel)){
      result++;
   }
   if(root->lc == sentinel){
        result += countNodes(root->rc);
   }
   else if(root->rc == sentinel){
        result += countNodes(root->lc);
   }
   else{
        result += (countNodes(root->lc) +
        countNodes(root->rc));
   }
   
   return result;
}

/**
 * @brief Finds the nth player in the player tree 
 *
 * @param root The root of the player tree where the search will begin
 *
 * @param n The number of the node we need to find in the tree
 */
void findNthInOrder(struct Player* root, int n){
    if(root == sentinel){
        return;
    }
    if(found != 1){
        findNthInOrder(root->lc, n);
        counter++;
        if(counter-1 == n){
            newPlayer = root;
            found = 1;
            return;
        }
        findNthInOrder(root->rc, n);
    }
}

/**
 * @brief Finds the nth player in the players tree
 *
 * @param root The root of the players tree
 * 
 * @param n The number of the player that we search for
 */
void findPlayer(struct Player* root, int n){
    if(root == sentinel){
        return;
    }
    findPlayer(root->lc, n);
    if(root->pid == n){
        newPlayer = root;
        return;
    }
    findPlayer(root->rc, n);
}

/**
 * @brief Finds the player with the biggest evidence number
 *
 * @param root The root of the players tree
 */
void findAlien(struct Player* root){
    if(root == sentinel){
        return;
    }
    findAlien(root->lc);
    if(alien->evidence < root->evidence){
        alien = root;
        return;
    }
    findAlien(root->rc);
}

/**
 * @brief Deletes a specific node in a player's task tree 
 *
 * @param root The root of the player's task tree
 *
 * @param tid The tid of the node that will be deleted
 *
 * @return The root to teh new task tree of the player
 */
struct Task* deleteInOrder(struct Task* root, int tid){
    if (root == NULL){
        return root;
    }
    if (tid < root->tid){
        root->lc = deleteInOrder(root->lc, tid);
    }
    else if (tid > root->tid){
        root->rc = deleteInOrder(root->rc, tid);
    }
    else{
        if(root->lc == NULL && root ->rc == NULL){
            insertPQ(completed_tasks_pq->tasks, root);
            root = NULL;
            return root;
        }
        if(root->lc == NULL){
            struct Task* temp = root->rc;
            insertPQ(completed_tasks_pq->tasks, root);
            free(root);
            return temp;
        }
        else if(root->rc == NULL){
            struct Task* temp = root->lc;
            insertPQ(completed_tasks_pq->tasks, root);
            free(root);
            return temp;
        }
        struct Task* temp = minValueNode(root->rc);
        root->tid = temp->tid;
        root->rc = deleteInOrder(root->rc, temp->tid);
    }
    return root;
}

/**
 * @brief Deletes a specific node from the players tree
 *
 * @param root The root of the players tree
 *
 * @param pid The pid of the player that will be deleted
 */
void deletePlayerInOrder(struct Player* root, int pid){
    if (root == sentinel){
        return;
    }
    if (pid < root->pid){
        deletePlayerInOrder(root->lc, pid);
    }
    else if (pid > root->pid){
        deletePlayerInOrder(root->rc, pid);
    }
    else{
        if(root->lc == sentinel && root ->rc == sentinel && root->parrent == NULL){
            root = sentinel;
            return;
        }
        if(root->lc == sentinel){
            if(root->pid < root->parrent->pid){
                root->rc->parrent = root->parrent;
                root->parrent->lc = root->rc;
                free(root);
                return;
            }
            else{
                root->rc->parrent = root->parrent;
                root->parrent->rc = root->rc;
                free(root);
                return;
            }
        }
        else if(root->rc == sentinel){
            if(root->pid < root->parrent->pid){
                root->lc->parrent = root->parrent;
                root->parrent->lc = root->lc;
                free(root);
                return;
            }
            else{
                root->lc->parrent = root->parrent;
                root->parrent->rc = root->lc;
                free(root);
                return;
            }
            free(root);
            return;
        }
        struct Player* temp = minValuePlayer(root->rc);
        root->pid = temp->pid;
        deletePlayerInOrder(root->rc, pid);
    }
}

/**
 * @brief Finds the leftmost node of this player's task tree
 *
 * @param node The point where the search will begin 
 *
 * @return The leftmost node of this player's task tree
 */
struct Task* minValueNode(struct Task* node)
{
    struct Task* current = node;
    while (current && current->lc != NULL){
        current = current->lc;
    }
    return current;
}

/**
 * @brief Finds the leftmost node of this players tree
 *
 * @param node The point where the search will begin 
 *
 * @return The leftmost node of this players tree
 */
struct Player* minValuePlayer(struct Player* node)
{
    struct Player* current = node;
    while (current != sentinel && current->lc != sentinel){
        current = current->lc;
    }
    return current;
}

/**
 * @brief Counts the nodes of the player's task left subtree
 *
 * @param root The point where the search will begin 
 *
 * @return The number of the nodes of the player's task left subtree
 */
void countNodesForLcnt(struct Task* root)
{
    if(root != NULL)
    {
        countNodesForLcnt(root->lc);
        counter++;
        countNodesForLcnt(root->rc);
    }
}

/**
 * @brief Calls the countNodesForLcnt function and updates the lcnt of the nodes
 *
 * @param root The node root of the player's task tree
 */
void updateLcnt(struct Task* head){
    struct Task* temp = head;
    if (head == NULL){
          return; 
    }
     updateLcnt(head->lc); 
     counter = 0;
     countNodesForLcnt(temp->lc);
     head->lcnt = counter;
     updateLcnt(head->rc);
}

/**
 * @brief Traverses the players tree recursively, used together with recurDoubleT on print_double_tree 
 *
 * @param root the root of the player's tree
 */
void recurDoubleP(struct Player* root){
    struct Task* task;
    if (root == sentinel || root == NULL){
          return; 
    }
    task = root->tasks;
     recurDoubleP(root->lc); 
     printf("\nPlayer %d= ", root->pid);
     recurDoubleT(task);
     recurDoubleP(root->rc);
}

/**
 * @brief Traverses through the players tree recursively and prints the evidence next to the player
 *
 * @param root The root of the player tree
 */
void recurDoublePEvidence(struct Player* root){
    struct Task* task;
    if (root == sentinel || root == NULL){
          return; 
    }
    task = root->tasks;
     recurDoublePEvidence(root->lc); 
     printf("\n<Player %d,Evidence %d>= ", root->pid, root->evidence);
     recurDoubleT(task);

     recurDoublePEvidence(root->rc);
}

/**
 * @brief Traverses the player's task tree recursively, used together with recurDoubleP on print_double_tree 
 *
 * @param root the root of the player's task tree
 */
void recurDoubleT(struct Task* task){
    if (task == NULL){
        return; 
    }
     recurDoubleT(task->lc); 
  
     printf("<%d,%d>", task->tid, task->difficulty);   
  
     recurDoubleT(task->rc);
}


/**
 * @brief Print Player & Evidence with task tree
 *
 * @return 1 on success
 *         0 on fail 
 */
int print_double_treeEvidence() {
    struct Player* curr;
    curr = players_tree;
    if (players_tree == NULL){
        return 1;
    }
    
    recurDoublePEvidence(curr);
    printf("\n \n");
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Swaps two nodes
 *
 * @param a A pointer to a pointer to a node  
 * 
 * @param b A pointer to a pointer to a node
 */
void swap(struct HT_Task *a, struct HT_Task *b){
    struct HT_Task* t;
    t = a;
    a = b;
    b = t;
}

/**
 * @brief Arranges the order of the heap memory of the priority queue
 *
 * @param array An array of the priority queue
 * 
 * @param size The size of the priority queue
 * 
 * @param i The number of teh largest node in the priority queue
 */
void heapify(struct HT_Task* array, int size, int i) {
    struct HT_Task* left, *right, *max;
    if (size == 1) {
    printf("Single element in the heap");
    } else {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        max = &array[largest];
        left = &array[l];
        right = &array[r];
        if (l < size && left->difficulty > max->difficulty){
            largest = l;
        }
        if (r < size && right->difficulty > max->difficulty){
            largest = r;
        }
        if (largest != i) {
            swap(&array[i], &array[largest]);
            heapify(array, size, largest);
        }
    }
}

/**
 * @brief Inserts a node to the priority queue
 *
 * @param array An array of the priority queue
 * 
 * @param newNode The node that will be inserted
 */
void insertPQ(struct HT_Task* array, struct Task* newNode) {
    struct HT_Task* temp;
    temp = (struct HT_Task*)malloc(sizeof(struct HT_Task*));
    temp->tid = newNode->tid;
    temp->difficulty = newNode->difficulty;
    if (completed_tasks_pq->size == 0) {
    array[0] = *temp;
    completed_tasks_pq->size += 1;
  } else {
    array[completed_tasks_pq->size] = *temp;
    completed_tasks_pq->size += 1;
    int i;
    for (i = completed_tasks_pq->size / 2 - 1; i >= 0; i--) {
      heapify(array, completed_tasks_pq->size, i);
    }
  }
}

/**
 * @brief Deletes a node from the priority queue
 *
 * @param array An array of the priority queue
 * 
 * @param Node The node that will be deleted
 */
void deleteRoot(struct HT_Task* array, struct Task* Node) {
  struct HT_Task* curr;  
  int i;
  for (i = 0; i < completed_tasks_pq->size; i++) {
    curr = &array[i];
    if (curr->tid == Node->tid){
      break;
    }
  }

  swap(&array[i], &array[completed_tasks_pq->size-1]);
  completed_tasks_pq->size -= 1;
  for (i = completed_tasks_pq->size / 2 - 1; i >= 0; i--) {
    heapify(array, completed_tasks_pq->size, i);
  }
}

/**
 * @brief Finds a non-alien parrent of a node
 */
struct Player* findInOrderPredecessor(){
    if(newPlayer->parrent->is_alien == 0 && newPlayer->parrent != sentinel){
        return newPlayer->parrent;
    }
    else{
        newPlayer = newPlayer->parrent;
        while(newPlayer->is_alien == 1 || newPlayer == sentinel){
            newPlayer = newPlayer->parrent;
        }
    }
    return newPlayer;
    
}

/**
 * @brief Finds the non-alien child of a node
 */
struct Player* findInOrderSucessor(){
    if(newPlayer->rc == sentinel && newPlayer->lc != sentinel){
        if(newPlayer->lc->is_alien == 0){
            return newPlayer->lc;
        }
        else{
            newPlayer = newPlayer->lc;
            while(newPlayer->is_alien == 1 || newPlayer == sentinel){
                if(newPlayer == sentinel){
                    newPlayer = players_tree;
                }
                if(newPlayer->lc->is_alien == 0){
                    newPlayer = newPlayer->lc;
                }
                else{
                    newPlayer = newPlayer->rc;
                }
            }
        }
        
    }
    else if(newPlayer->lc == sentinel && newPlayer->rc != sentinel){
        if(newPlayer->rc->is_alien == 0){
            return newPlayer->lc;
        }
        else{
            newPlayer = newPlayer->rc;
            while(newPlayer->is_alien == 1 || newPlayer == sentinel){
                if(newPlayer == sentinel){
                    newPlayer = players_tree;
                }
                if(newPlayer->rc->is_alien == 0){
                    newPlayer = newPlayer->rc;
                }
                else{
                    newPlayer = newPlayer->lc;
                }
            }
        }
    }
    else if(newPlayer->lc != sentinel && newPlayer->rc != sentinel){
        if(counter == 1){
            return newPlayer->rc;
        }
        else{
            if(newPlayer->lc->is_alien == 0){
                return newPlayer->lc;
            }
            else{
                newPlayer = newPlayer->lc;
                while(newPlayer->is_alien == 1 || newPlayer == sentinel){
                    if(newPlayer == sentinel){
                        newPlayer = players_tree;
                    }
                    if(newPlayer->lc->is_alien == 0){
                        newPlayer = newPlayer->lc;
                    }
                    else{
                        newPlayer = newPlayer->rc;
                    }
                }
            }
        }
    }
    else{
        newPlayer = players_tree;
        counter = 1;
        if(newPlayer->is_alien == 0){
            return newPlayer;
        }
    }
    return findInOrderSucessor();
}

/**
 * @brief Inserts a task in a player's task tree
 *
 * @param task The task that will be inserted
 * 
 * @param base The player to which the task will be assigned 
 */
void insertTask(struct Task* task, struct Player* base){
    struct Task* root;
    root = base->tasks;
    if(base->tasks == NULL){
        task->lc = base->tasks;
        task->rc = base->tasks;
        base->tasks = task;
        return;
    }
    else if((base->tasks) && ((base->tasks->lc == NULL) && (base->tasks->rc == NULL))){
        if(task->tid < root->tid){
            task->lc = NULL;
            task->rc = NULL;
            root->lc = task;
        }
        else{
            task->lc = NULL;
            task->rc = NULL;
            root->rc = task;
            return;
        }
    }
    else{
        while((root->lc != NULL) || (root->rc != NULL)){
            if((root->lc == NULL) && (task->tid < root->tid)){
                task->lc = NULL;
                task->rc = NULL;
                root->lc = task;
                break;
            }
            else if((root->rc == NULL) && (task->tid > root->tid)){
                task->lc = NULL;
                task->rc = NULL;
                root->rc = task;
                break;
            }
            else{
                if(task->tid < root->tid){
                    root = root->lc;
                }
                else{
                     root = root->rc;
                }
            }
        }
        if(task->tid < root->tid){
            task->lc = NULL;
            task->rc = NULL;
            root->lc = task;
        }
        else{
            task->lc = NULL;
            task->rc = NULL;
             root->rc = task;
        }
    }
    updateLcnt(root);
}

/**
 * @brief Finds the total number of tasks in a player's task tree
 *
 * @param root The root of the player's tree
 *
 * @return The number of the tasks in the player's task tree
 */
int findNumberOfTasks(struct Task* root, int n){
    if(root == NULL){
        return n;
    }
    return n = 1 + findNumberOfTasks(root->lc, n) + findNumberOfTasks(root->rc, n);
}

/**
 * @brief Counts the alien nodes of the players tree
 *
 * @param root The root of the players tree
 */
void findNumberOfAliens(struct Player* root){
    if(root == NULL){
        return;
    }
    findNumberOfPlayers(root->lc);
    if(root->is_alien == 1){
        counter++;
    }
    findNumberOfAliens(root->rc);
}

/**
 * @brief Counts the crewmate nodes of the players tree
 *
 * @param root The root of the players tree
 */
void findNumberOfPlayers(struct Player* root){
    if(root == NULL){
        return;
    }
    findNumberOfPlayers(root->lc);
    if(root->is_alien == 0){
        found++;
    }
    findNumberOfPlayers(root->rc);
}
