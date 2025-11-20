#ifndef BST_H
#define BST_H

#define NAME_LEN 50
#define DISEASE_LEN 50
#define DATETIME_LEN 32

typedef struct Patient {
    int id;
    char name[NAME_LEN];
    int age;
    char disease[DISEASE_LEN];
} Patient;

typedef struct node {
    Patient* data;
    struct node* left;
    struct node* right;
} node;

typedef struct Appointment {
    int patient_id;
    char datetime[DATETIME_LEN];
    struct Appointment* next;
} Appointment;

node* createNode(Patient* payload);
node* insertNode(node* root, Patient* data);
node* searchNode(node* root, int id);
node* findMin(node* root);
node* findMax(node* root);
node* deleteNode(node* root, int id);
void printPatient(Patient* p);
void inorderTraversal(node* root);
void preorderTraversal(node* root);
void postorderTraversal(node* root);
void freeTree(node* root);
Patient* createPatient();
void scheduleAppointment(node* root);
void printAppointments();
void removeAppointmentsByPatient(int pid);
void freeAppointments();
void findPatientsInRange(node* root, int minID, int maxID);
int getPatientCount(node* root);

#endif


