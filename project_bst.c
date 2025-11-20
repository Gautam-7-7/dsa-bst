#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project_bst.h"

static Appointment* appt_head = NULL;

node* createNode(Patient* payload) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL)
        return NULL;
    newNode->data = payload;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node* insertNode(node* root, Patient* data) {
    if (root == NULL)
        return createNode(data);
    if (data->id < root->data->id)
        root->left = insertNode(root->left, data);
    else if (data->id > root->data->id)
        root->right = insertNode(root->right, data);
    return root;
}

node* searchNode(node* root, int id) {
    if (root == NULL)
        return NULL;
    if (id == root->data->id)
        return root;
    if (id < root->data->id)
        return searchNode(root->left, id);
    return searchNode(root->right, id);
}

node* findMin(node* root) {
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

node* findMax(node* root) {
    while (root != NULL && root->right != NULL)
        root = root->right;
    return root;
}

node* deleteNode(node* root, int id) {
    if (root == NULL)
        return NULL;
    if (id < root->data->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->data->id)
        root->right = deleteNode(root->right, id);
    else {
        if (root->left == NULL || root->right == NULL) {
            node* temp;
            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;
            free(root->data);
            free(root);
            return temp;
        }
        node* temp = findMin(root->right);
        *(root->data) = *(temp->data);
        root->right = deleteNode(root->right, temp->data->id);
    }
    return root;
}

void printPatient(Patient* p) {
    if (!p) return;
    printf("ID: %d, Name: %s, Age: %d, Disease: %s\n", p->id, p->name, p->age, p->disease);
}

void inorderTraversal(node* root) {
    if (root) {
        inorderTraversal(root->left);
        printPatient(root->data);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(node* root) {
    if (root) {
        printPatient(root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(node* root) {
    if (root) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printPatient(root->data);
    }
}

void freeTree(node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root->data);
    free(root);
}

Patient* createPatient() {
    Patient* p = (Patient*)malloc(sizeof(Patient));
    if (!p) return NULL;
    printf("Enter Patient ID: ");
    scanf("%d", &p->id);
    printf("Enter Name: ");
    scanf("%s", p->name);
    printf("Enter Age: ");
    scanf("%d", &p->age);
    printf("Enter Disease: ");
    scanf("%s", p->disease);
    return p;
}

static void addAppointmentInternal(int pid, const char* dt) {
    Appointment* a = (Appointment*)malloc(sizeof(Appointment));
    if (!a) return;
    a->patient_id = pid;
    strncpy(a->datetime, dt, DATETIME_LEN - 1);
    a->datetime[DATETIME_LEN - 1] = '\0';
    a->next = appt_head;
    appt_head = a;
}

void removeAppointmentsByPatient(int pid) {
    Appointment* cur = appt_head;
    Appointment* prev = NULL;
    while (cur) {
        if (cur->patient_id == pid) {
            Appointment* t = cur;
            if (prev) prev->next = cur->next;
            else appt_head = cur->next;
            cur = cur->next;
            free(t);
            continue;
        }
        prev = cur;
        cur = cur->next;
    }
}

void printAppointments() {
    if (!appt_head) {
        printf("No appointments scheduled.\n");
        return;
    }
    Appointment* a = appt_head;
    while (a) {
        printf("Patient ID: %d, Time: %s\n", a->patient_id, a->datetime);
        a = a->next;
    }
}

void freeAppointments() {
    Appointment* cur = appt_head;
    while (cur) {
        Appointment* t = cur;
        cur = cur->next;
        free(t);
    }
    appt_head = NULL;
}

void scheduleAppointment(node* root) {
    int pid;
    char dt[DATETIME_LEN];
    printf("Enter patient ID for appointment: ");
    if (scanf("%d", &pid) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }
    node* found = searchNode(root, pid);
    if (!found) {
        printf("Patient not found.\n");
        return;
    }
    printf("Enter datetime (e.g. 2025-11-12_14:30): ");
    scanf("%s", dt);
    addAppointmentInternal(pid, dt);
    printf("Appointment added for %s at %s\n", found->data->name, dt);
}

void findPatientsInRange(node* root, int minID, int maxID) {
    if (!root) return;
    if (root->data->id > minID)
        findPatientsInRange(root->left, minID, maxID);
    if (root->data->id >= minID && root->data->id <= maxID)
        printPatient(root->data);
    if (root->data->id < maxID)
        findPatientsInRange(root->right, minID, maxID);
}

int getPatientCount(node* root) {
    if (!root) return 0;
    return 1 + getPatientCount(root->left) + getPatientCount(root->right);
}
