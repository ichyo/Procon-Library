// 三角形の内心
// verify : aoj 1301
P incenter(P p1, P p2, P p3){
    double a = abs(p2 - p3);
    double b = abs(p3 - p1);
    double c = abs(p1 - p2);
    return (a * p1 + b * p2 + c * p3) / (a + b + c);
}

