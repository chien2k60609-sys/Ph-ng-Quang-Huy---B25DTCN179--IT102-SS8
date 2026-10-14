#include <stdio.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    int actual_fee;
};

int main() {
    struct UserAccount accounts[100];
    int n, i;
    int total_revenue = 0;
    int downgraded_count = 0;

    printf("Nhap so luong tai khoan (1 - 100): ");
    scanf("%d", &n);
    while (n < 1 || n > 100) {
        printf("So luong khong hop le! Nhap lai (1 - 100): ");
        scanf("%d", &n);
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);
        printf("Ma tai khoan: ");
        scanf("%d", &accounts[i].user_id);
        printf("Ten tai khoan: ");
        scanf(" %[^\n]", accounts[i].username);

        do {
            printf("Loai goi (1: Free, 2: Personal, 3: Family): ");
            scanf("%d", &accounts[i].plan_type);
            if (accounts[i].plan_type < 1 || accounts[i].plan_type > 3) {
                printf("[LOI DU LIEU] Loai goi phai thuoc [1, 3]! Nhap lai.\n");
            }
        } while (accounts[i].plan_type < 1 || accounts[i].plan_type > 3);

        do {
            printf("So ngay no cuoc: ");
            scanf("%d", &accounts[i].days_overdue);
            if (accounts[i].days_overdue < 0) {
                printf("[LOI DU LIEU] So ngay no cuoc khong duoc am! Nhap lai.\n");
            }
        } while (accounts[i].days_overdue < 0);

        do {
            printf("So thiet bi dang ket noi: ");
            scanf("%d", &accounts[i].active_devices);
            if (accounts[i].active_devices < 0) {
                printf("[LOI DU LIEU] So thiet bi khong duoc am! Nhap lai.\n");
            }
        } while (accounts[i].active_devices < 0);
    }

    for (i = 0; i < n; i++) {
        if (accounts[i].days_overdue >= 3) {
            accounts[i].plan_type = 1;
            downgraded_count++;
        }

        if (accounts[i].plan_type == 1) {
            accounts[i].actual_fee = 0;
        } else if (accounts[i].plan_type == 2) {
            accounts[i].actual_fee = 120000;
            if (accounts[i].active_devices > 1) {
                accounts[i].actual_fee += (accounts[i].active_devices - 1) * 30000;
            }
        } else if (accounts[i].plan_type == 3) {
            accounts[i].actual_fee = 250000;
        }

        total_revenue += accounts[i].actual_fee;
    }

    printf("\n=== BANG DOI SOAT THONG TIN TAI KHOAN ===\n");
    printf("%-10s %-20s %-10s %-15s %-15s %-15s\n", 
           "MA TK", "TEN TK", "MA GOI", "SO THIET BI", "NO CUOC (NGAY)", "PHI THUC THU");
    printf("------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-20s %-10d %-15d %-15d %-15d\n",
               accounts[i].user_id,
               accounts[i].username,
               accounts[i].plan_type,
               accounts[i].active_devices,
               accounts[i].days_overdue,
               accounts[i].actual_fee);
    }

    printf("------------------------------------------------------------------------------------\n");
    printf("Tong doanh thu thuc te trong ky : %d VND\n", total_revenue);
    printf("So tai khoan bi ha cap ve Free  : %d\n", downgraded_count);

    return 0;
}

