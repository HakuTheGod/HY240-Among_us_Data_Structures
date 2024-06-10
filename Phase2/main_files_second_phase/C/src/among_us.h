/**************************************************
 *                                                *
 * file: among_us.h                               *
 *                                                *
 *                                                *
 * @Author  Skerdi Basha                          *
 * @Version 1-12-2020                             *
 * @email   sbash@csd.uoc.gr                      *
 *                                                *
 * @brief   Header file for the needs of CS-240   *
 * project 2020, with the structures and function *
 * prototypes                                     *
 *                                                *
 **************************************************
 */

#ifndef __AMONG_US_H_
#define __AMONG_US_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Structure defining a node of the players double linked tree
 * tree
 */
struct Player
{
    int pid;                        /*Player's identifier*/
    int is_alien;                   /*Alien flag*/
    int evidence;                   /*Amount of evidence*/
    struct Player *parrent;         /*Pointer to the parent node*/
    struct Player *lc;              /*Pointer to the left child node*/
    struct Player *rc;              /*Pointer to the right child node*/
    struct Task *tasks;             /*Pointer to the head of player's task tree*/
};

/**
 * Structure defining a node of the tasks sorted tree
 */
struct Task
{
    int tid;                        /*Task's identifier*/
    int difficulty;                 /*Task's difficulty*/
    int lcnt;                       /*Node's left child's node counter*/
    struct Task *lc;                /*Pointer to the left child node*/
    struct Task *rc;                /*Pointer to the right child node*/ 
};

struct HT_Task
{
    int tid;                        /*Task's identifier*/
    int difficulty;                 /*Task's difficulty*/
    struct HT_Task *next;           /*Pointer to the next node*/
};

struct General_Tasks_HT
{
    int count;                      /*Count of tasks*/
    struct HT_Task **tasks;         /*General tasks hash table*/
};

struct Completed_Tasks_PQ
{
    int size;                       /*Count of completed tasks*/
    struct HT_Task *tasks;         /*Completed tasks priority queue*/
};

unsigned int max_tasks_g; /* Max number of tasks */
unsigned int max_tid_g;   /* Max task tid */

/* Primes for your universal hashing implementation */
extern unsigned int primes_g[650];

/* Global variable, pointer to the head of the players tree */
struct Player *players_tree;
struct Player *sentinel;

/* Global variable, pointer to the head of the tasks tree */
struct General_Tasks_HT *general_tasks_ht;

/* Global variable, pointer to the top of the completed task's priority queue */
struct Completed_Tasks_PQ *completed_tasks_pq;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize();

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien);

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
int insert_task(int tid, int difficulty);

/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks();

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
int implement_task(int pid, int tid);

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
int eject_player(int pid_1, int pid_2);

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
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses);

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
int sabotage(int number_of_tasks, int pid);

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
int vote(int pid_1, int pid_2, int vote_evidence);

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
int give_work(int pid_1, int pid_2);

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate();

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players();

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks();

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq();

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree();

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void);

/**
 * @brief Print the players recursively
 *
 * @param root The player's tree root
 * 
 */
void recur(struct Player* root);

/**
 * @brief Inserts the task tree of a player to another player's task tree
 *
 * @param taskP1 The root of the giving player's task tree
 *
 * @param taskP2 the root of the recieving player's task tree
 *
 */
void insertToTree(struct Task* taskP1, struct Task* taskP2);

/**
 * @brief Hash function for the hash table
 *
 * @param tid The current task's tid
 *
 * @return the resault of the hash function
 */
int hashFunction(int tid);

/**
 * @brief counts the nodes of the player tree
 *
 * @param root The root of the player tree
 *
 * @return The number of the player nodes on success 
 *         0 on failure
 */
int countNodes(struct Player* root);

/**
 * @brief Finds the nth player in the player tree 
 *
 * @param root The root of the player tree where the search will begin
 *
 * @param n The number of the node we need to find in the tree
 */
void findNthInOrder(struct Player* root, int n);

/**
 * @brief Traverses the players tree recursively, used together with recurDoubleT on print_double_tree 
 *
 * @param root the root of the player's tree
 */
void recurDoubleP(struct Player* root);

/**
 * @brief Traverses the player's task tree recursively, used together with recurDoubleP on print_double_tree 
 *
 * @param root the root of the player's task tree
 */
void recurDoubleT(struct Task* task);

/**
 * @brief Deletes a specific node in a player's task tree 
 *
 * @param root The root of the player's task tree
 *
 * @param tid The tid of the node that will be deleted
 *
 * @return The root to teh new task tree of the player
 */
struct Task* deleteInOrder(struct Task* root, int tid);

/**
 * @brief Deletes a specific node from the players tree
 *
 * @param root The root of the players tree
 *
 * @param pid The pid of the player that will be deleted
 */
void deletePlayerInOrder(struct Player* root, int pid);

/**
 * @brief Finds the leftmost node of this player's task tree
 *
 * @param node The point where the search will begin 
 *
 * @return The leftmost node of this player's task tree
 */
struct Task* minValueNode(struct Task* node);

/**
 * @brief Finds the leftmost node of this players tree
 *
 * @param node The point where the search will begin 
 *
 * @return The leftmost node of this players tree
 */
struct Player* minValuePlayer(struct Player* node);

/**
 * @brief Counts the nodes of the player's task left subtree
 *
 * @param root The point where the search will begin 
 *
 * @return The number of the nodes of the player's task left subtree
 */
void countNodesForLcnt(struct Task* root);

/**
 * @brief Calls the countNodesForLcnt function and updates the lcnt of the nodes
 *
 * @param root The node root of the player's task tree
 */
void updateLcnt(struct Task* root);

/**
 * @brief Finds the nth player in the players tree
 *
 * @param root The root of the players tree
 * 
 * @param n The number of the player that we search for
 */
void findPlayer(struct Player* root, int n);

/**
 * @brief Traverses through the players tree recursively and prints the evidence next to the player
 *
 * @param root The root of the player tree
 */
void recurDoublePEvidence(struct Player* root);

/**
 * @brief Print Player & Evidence with task tree
 *
 * @return 1 on success
 *         0 on fail 
 */
int print_double_treeEvidence();

/**
 * @brief Swaps two nodes
 *
 * @param a A pointer to a pointer to a node  
 * 
 * @param b A pointer to a pointer to a node
 */
void swap(struct HT_Task *a, struct HT_Task *b);

/**
 * @brief Arranges the order of the heap memory of the priority queue
 *
 * @param array An array of the priority queue
 * 
 * @param size The size of the priority queue
 * 
 * @param i The number of teh largest node in the priority queue
 */
void heapify(struct HT_Task* array, int size, int i);

/**
 * @brief Inserts a node to the priority queue
 *
 * @param array An array of the priority queue
 * 
 * @param newNode The node that will be inserted
 */
void insertPQ(struct HT_Task* array, struct Task* newNode);

/**
 * @brief Deletes a node from the priority queue
 *
 * @param array An array of the priority queue
 * 
 * @param Node The node that will be deleted
 */
void deleteRoot(struct HT_Task* array, struct Task* Node);

/**
 * @brief Finds a non-alien parrent of a node
 */
struct Player* findInOrderPredecessor();

/**
 * @brief Finds the non-alien child of a node
 */
struct Player* findInOrderSucessor();

/**
 * @brief Inserts a task in a player's task tree
 *
 * @param task The task that will be inserted
 * 
 * @param base The player to which the task will be assigned 
 */
void insertTask(struct Task* task, struct Player* base);

/**
 * @brief Finds the player with the biggest evidence number
 *
 * @param root The root of the players tree
 */
void findAlien(struct Player* root);

/**
 * @brief Finds the total number of tasks in a player's task tree
 *
 * @param root The root of the player's tree
 *
 * @return The number of the tasks in the player's task tree
 */
int findNumberOfTasks(struct Task* root, int n);

/**
 * @brief Counts the alien nodes of the players tree
 *
 * @param root The root of the players tree
 */
void findNumberOfAliens(struct Player* root);

/**
 * @brief Counts the crewmate nodes of the players tree
 *
 * @param root The root of the players tree
 */
void findNumberOfPlayers(struct Player* root);

/* Global Variables */
/* Used in many functions to hold values instead of statict variable */
int counter;

/* Used in many functions to hold values instead of statict variable */
int found;

/* Used in many functions to hold player nodes */
struct Player* newPlayer;

/* Used in many functions to hold alien nodes */
struct Player* alien;

/* Used in many functions to hold task nodes */
struct Task* taskA;
#endif /* __AMONG_US_H_ */
