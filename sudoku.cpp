#include<bits/stdc++.h>
using namespace std;
using VVI = vector<vector<int>>;

const int TABLE_SIZE = 9; // 9 * 9のサイズ前提 
const vector<int> CONVERT_LIST{0b0, 0b100000000, 0b10000000, 0b1000000, 0b100000, 0b10000, 0b1000, 0b100, 0b10, 0b1};
bool isDiscovered = false;

void input(VVI &table) {
    // ここだけでしか使えないってのがあるが妥協...
    ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());

    for(int i = 0;i < TABLE_SIZE;i++) {
        for(int j = 0;j < TABLE_SIZE;j++) {
            int tmp; cin >> tmp;
            table[i][j] = tmp;
        }
    }
}
int checkRow(VVI table, int row) {
    int ableRowFlg = 0b1111111111;
    for(int i = 0;i < TABLE_SIZE;i++) {
        if(table[row][i] != 0) {
            ableRowFlg = ableRowFlg ^ CONVERT_LIST[table[row][i]];  
        }
    }
    return ableRowFlg;
}
int checkCol(VVI table, int col) {
    int ableColFlg = 0b1111111111; //  0123456789
                                   //  ----------
                                   //0b1111111111 各桁が上の数に対応
    for(int i = 0;i < TABLE_SIZE;i++) {
        if(table[i][col] != 0) {
            ableColFlg = ableColFlg ^ CONVERT_LIST[table[i][col]];  
        }
    }
    return ableColFlg;
}
int checkBox(VVI table, int row, int col) {
    int upperLeftRowOfBow = row / 3 * 3;
    int upperLeftColOfBow = col / 3 * 3;

    int ableBoxFlg = 0b1111111111;
    for(int i = upperLeftRowOfBow;i < upperLeftRowOfBow + 3;i++) {
        for(int j = upperLeftColOfBow;j < upperLeftColOfBow + 3;j++) {
            if(table[i][j] != 0) {
                ableBoxFlg = ableBoxFlg ^ CONVERT_LIST[table[i][j]];
            }
        }
    }
    return ableBoxFlg;
}

void output(VVI table) {
    for(int i = 0;i < TABLE_SIZE;i++) {
        for(int j = 0;j < TABLE_SIZE;j++) {
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }
}
void solve(VVI table, int row, int col, int value) {
    if(table[row][col] == 0) {
        table[row][col] = value;
    }
    while(table[row][col] != 0) {
        col += 1; // 次の列へ移動
        if(col == TABLE_SIZE) { // 現在の列が端の次の列なら次の行に移動
            col = 0;
            row++;
        }
        if(row >= TABLE_SIZE) break;
    }

    if(row < TABLE_SIZE) {
        int ableNumFlg = checkRow(table, row) & checkCol(table, col) & checkBox(table, row, col);
        for(int i = 1;i <= TABLE_SIZE;i++) {
            if(!(ableNumFlg & (0b1000000000 >> i))) continue;
            if(isDiscovered) return;
            solve(table, row, col, i);
        }
    } else {
        output(table);
        isDiscovered = true;
    }
}
int main() {
    VVI table(TABLE_SIZE, vector<int>(TABLE_SIZE));
    input(table);

    if(table[0][0] == 0) {
        int ableNumFlg = checkRow(table, 0) & checkCol(table, 0) & checkBox(table, 0, 0);
        for(int i = 1;i <= TABLE_SIZE;i++) {
            if(!(ableNumFlg & (0b1000000000 >> i))) continue;
            if(isDiscovered) return 0;
            solve(table, 0, 0, i);
        }
    } else {
        solve(table, 0, 0, table[0][0]);
    }
    return 0;
}