auto& printSTD = FILL_THIS_IN;
cout << "[";
bool printNotFirst = false;
for (auto val : printSTD) {
    if (printNotFirst) cout << ", ";
    printNotFirst = true;
    cout << val;
}
cout << "]" << endl;
