auto& printMap = FILL_THIS_IN;
cout << "{";
bool printNotFirst = false;
for (auto x : printMap) {
    if (printNotFirst) cout << ", ";
    printNotFirst = true;
    cout << x.first << ": " << x.second;
}
cout << "}" << endl;
