#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    struct UserAccount accounts[100];
    struct UserAccount temp;
    int n, i, j;
    int mrr_initial = 0;
    int mrr_actual = 0;
    int max_allowed_devices;

    printf("Nhap so luong tai khoan (1 - 100): ");
    scanf("%d", &n);
    while (n < 1 || n > 100) {
        printf("So luong khong hop le! Nhap lai (1 - 100): ");
        scanf("%d", &n);
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan %d ---\n", i + 1);
        printf("Ma tai khoan: ");
        scanf("%d", &accounts[i].account_id);

        do {
            printf("Loai goi (0: Free, 1: Standard, 2: Premium): ");
            scanf("%d", &accounts[i].plan_type);
            if (accounts[i].plan_type < 0 || accounts[i].plan_type > 2) {
                printf("[LOI DU LIEU] Loai goi phai thuoc [0, 2]!\n");
            }
        } while (accounts[i].plan_type < 0 || accounts[i].plan_type > 2);

        printf("Phi goi hang thang (VND): ");
        scanf("%d", &accounts[i].monthly_fee);

        printf("So ngay su dung con lai: ");
        scanf("%d", &accounts[i].remaining_days);

        printf("So thiet bi dang ket noi: ");
        scanf("%d", &accounts[i].active_devices);

        mrr_initial += accounts[i].monthly_fee;
    }

    for (i = 0; i < n; i++) {
        if (accounts[i].active_devices <= 0) {
            accounts[i].active_devices = 1;
        }

        if (accounts[i].remaining_days <= 0) {
            accounts[i].plan_type = 0;
            accounts[i].monthly_fee = 0;
            if (accounts[i].remaining_days < 0) {
                accounts[i].remaining_days = 0;
            }
        } else {
            if (accounts[i].plan_type == 1) {
                accounts[i].monthly_fee = 120000;
            } else if (accounts[i].plan_type == 2) {
                accounts[i].monthly_fee = 300000;
            } else {
                accounts[i].monthly_fee = 0;
            }
        }

        if (accounts[i].plan_type == 2) {
            max_allowed_devices = 5;
        } else if (accounts[i].plan_type == 1) {
            max_allowed_devices = 2;
        } else {
            max_allowed_devices = 1;
        }

        if (accounts[i].active_devices > max_allowed_devices) {
            accounts[i].active_devices = max_allowed_devices;
        }

        mrr_actual += accounts[i].monthly_fee;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int swap_needed = 0;

            if (accounts[j].plan_type == 0 && accounts[j + 1].plan_type > 0) {
                swap_needed = 1;
            } else if (accounts[j].plan_type > 0 && accounts[j + 1].plan_type > 0) {
                if (accounts[j].monthly_fee < accounts[j + 1].monthly_fee) {
                    swap_needed = 1;
                }
            }

            if (swap_needed) {
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }

    printf("\n=== BANG DANH SACH TAI KHOAN SAU KIEM TOAN & SAP XEP ===\n");
    printf("%-10s %-10s %-15s %-15s %-15s\n",
           "MA TK", "GOI CUOC", "PHI THANG", "NGAY CON LAI", "THIET BI");
    printf("-------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-10d %-15d %-15d %-15d\n",
               accounts[i].account_id,
               accounts[i].plan_type,
               accounts[i].monthly_fee,
               accounts[i].remaining_days,
               accounts[i].active_devices);
    }

    printf("-------------------------------------------------------------------\n");
    printf("Bao cao Doanh thu MRR Ban dau  : %d VND\n", mrr_initial);
    printf("Bao cao Doanh thu MRR Th?c te  : %d VND\n", mrr_actual);
    printf("Chênh l?ch thât thoát doanh thu: %d VND\n", mrr_initial - mrr_actual);

    return 0;
}

