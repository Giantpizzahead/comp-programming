auto& printArr = FILL_THIS_IN;
cout << "[";
for (int i = 0; i < sizeof(printArr)/sizeof(*printArr); i++) {
    if (i != 0) cout << "," << endl << " ";
    for (int j = 0; j < sizeof(printArr[i])/sizeof(*printArr[i]); j++) {
        if (j != 0) cout << ", ";
        cout << printArr[i][j];
    }
}
cout << "]" << endl;
