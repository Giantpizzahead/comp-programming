auto& printArr = FILL_THIS_IN;
cout << "[";
for (int i = 0; i < sizeof(printArr)/sizeof(*printArr); i++) {
    if (i != 0) cout << ", ";
    cout << printArr[i];
}
cout << "]" << endl;
