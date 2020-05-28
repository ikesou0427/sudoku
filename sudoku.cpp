#include<bits/stdc++.h>
using namespace std;
using VVI = vector<vector<int>>;
const int TABLE_SIZE = 9;
bool isDiscovered = false;
// 9 * 9のサイズ前提 そのうち改造

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
bool checkRow(VVI table, int row, int col, int value) {
    for(int i = 0;i < row;i++) {
        if(table[i][col] == value) return false;
    }
    for(int i = row + 1;i < TABLE_SIZE;i++) {
        if(table[i][col] == value) return false;
    }
    return true;
}
bool checkCol(VVI table, int row, int col, int value) {
    for(int i = 0;i < col;i++) {
        if(table[row][i] == value) return false;
    }
    for(int i = col + 1;i < TABLE_SIZE;i++) {
        if(table[row][i] == value) return false;
    }
    return true;
}
bool checkBox(VVI table, int row, int col, int value) {
    int upperLeftRowOfBow = row / 3 * 3;
    int upperLeftColOfBow = col / 3 * 3;

    for(int i = upperLeftRowOfBow;i < upperLeftRowOfBow + 3;i++) {
        for(int j = upperLeftColOfBow;j < upperLeftColOfBow + 3;j++) {
            if(table[i][j] == value) return false;
        }
    }
    return true;
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
    // for(int j = 0;j < TABLE_SIZE;j++) {
    //     cout << table[0][j] << " ";
    // }
    // cout << endl;
    
    cout << "対象マス(" << row + 1 << "行 " << col + 1 << "列) 代入予定: " << value << "\n";
    output(table);
    cout << endl;
    if(row >= TABLE_SIZE) {
        output(table);
        isDiscovered = true;
    } else {
        
        if(table[row][col] == 0) {
            if(!checkRow(table, row, col, value)) return;
            if(!checkCol(table, row, col, value)) return;
            if(!checkBox(table, row, col, value)) return;
            table[row][col] = value;

            col += 1; // 次の列へ移動
            if(col == TABLE_SIZE) { // 現在の列が端の次の列なら次の行に移動
                col = 0;
                row++;
            }
        } else {
            while(table[row][col] != 0) {
                col += 1; // 次の列へ移動
                if(col == TABLE_SIZE) { // 現在の列が端の次の列なら次の行に移動
                    col = 0;
                    row++;
                }
            }
        }

        for(int i = 1;i <= TABLE_SIZE;i++) {
            if(isDiscovered) return;
            solve(table, row, col, i);
        }
    } 
}
int main() {
    VVI table(TABLE_SIZE, vector<int>(TABLE_SIZE));
    input(table);

    if(table[0][0] == 0) {
        for(int i = 1;i <= TABLE_SIZE;i++) {
            solve(table , 0, 0, i);
        }
    } else {
        solve(table, 0, 0, table[0][0]);
    }
   
    return 0;
}