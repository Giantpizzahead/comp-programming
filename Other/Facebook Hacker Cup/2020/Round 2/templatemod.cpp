ll X[MAXN];
ll Ax, Bx, Cx, Dx;

for (int i = 0; i < K; i++) {
    fin >> X[i];
}
fin >> Ax >> Bx >> Cx >> Dx;
for (int i = K; i < N; i++) {
    X[i] = ((Ax * X[i-2] + Bx * X[i-1] + Cx) % Dx) + 1;
}
//*
for (int i = 0; i < N; i++) {
    cout << X[i] << ' ';
}
cout << endl;
//*/