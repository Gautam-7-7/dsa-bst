#include <stdio.h>
#include <stdlib.h>
#include "project_bst.h"

int main() {
    node* root = NULL;
    int choice, id, minID, maxID;

    while (1) {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Register Patient\n");
        printf("2. Remove Patient\n");
        printf("3. Search Patient\n");
        printf("4. Display All Patients (Inorder)\n");
        printf("5. Display Preorder\n");
        printf("6. Display Postorder\n");
        printf("7. Schedule Appointment\n");
        printf("8. View Appointments\n");
        printf("9. Emergency (Lowest ID)\n");
        printf("10. Find Patients in ID Range\n");
        printf("11. Get Patient Count\n");
        printf("12. Exit\n");
        printf("Choose option: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }

        if (choice == 1) {
            Patient* p = createPatient();
            if (!p) continue;
            if (searchNode(root, p->id)) {
                printf("Patient with this ID already exists.\n");
                free(p);
            } else {
                root = insertNode(root, p);
                printf("Patient registered.\n");
            }

        } else if (choice == 2) {
            printf("Enter Patient ID to remove: ");
            if (scanf("%d", &id) != 1) {
                while (getchar() != '\n');
                printf("Invalid input.\n");
                continue;
            }
            root = deleteNode(root, id);
            removeAppointmentsByPatient(id);
            printf("Patient removed if existed.\n");

        } else if (choice == 3) {
            printf("Enter Patient ID to search: ");
            if (scanf("%d", &id) != 1) {
                while (getchar() != '\n');
                printf("Invalid input.\n");
                continue;
            }
            node* result = searchNode(root, id);
            if (result)
                printPatient(result->data);
            else
                printf("Patient not found.\n");

        } else if (choice == 4) {
            inorderTraversal(root);

        } else if (choice == 5) {
            preorderTraversal(root);

        } else if (choice == 6) {
            postorderTraversal(root);

        } else if (choice == 7) {
            scheduleAppointment(root);

        } else if (choice == 8) {
            printAppointments();

        } else if (choice == 9) {
            node* first = findMin(root);
            if (first)
                printPatient(first->data);
            else
                printf("No patients.\n");

        } else if (choice == 10) {
            printf("Enter min ID: ");
            scanf("%d", &minID);
            printf("Enter max ID: ");
            scanf("%d", &maxID);
            if (minID > maxID) {
                printf("Invalid range.\n");
                continue;
            }
            findPatientsInRange(root, minID, maxID);

        } else if (choice == 11) {
            int count = getPatientCount(root);
            printf("Total patients: %d\n", count);

        } else if (choice == 12) {
            freeTree(root);
            freeAppointments();
            break;

        } else {
            printf("Invalid option.\n");
        }
    }
    return 0;
}

