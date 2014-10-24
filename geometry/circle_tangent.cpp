// 円の接線 (中心から偏角thの点で接する接線)
// verified: AOJ 2201
L circle_tangent(const C& c, double th){
    P p0 = c.p + polar(c.r, th);
    P p1 = p0 + polar(1.0, th + M_PI / 2);
    return {p0, p1};
}

// 二つの円の共通接線 (cの中心から接点へのベクトルの偏角を返す)
// verified: AOJ 2201
// 参考: http://geom.web.fc2.com/geometry/circle-circle-tangent.html
vector<double> common_tangents(const C& c, const C& d){
    vector<double> res;
    P v = d.p - c.p;
    double l = abs(v); // 二円の中心間の距離
    double a = arg(v); // 二円の中心間の偏角
    if(sign(l - abs(c.r - d.r)) > 0){
        // 交わる or 外接 or 離れている
        // 二つの外側接線
        double a1 = acos((c.r - d.r) / l);
        res.push_back(a + a1);
        res.push_back(a - a1);
        if(sign(l - (c.r + d.r)) > 0){
            // 離れている
            // 二つの内側接線
            double a2 = acos((c.r + d.r) / l);
            res.push_back(a + a2);
            res.push_back(a - a2);
        }
    }
    if((sign(l - abs(c.r - d.r)) == 0 || sign(l - (c.r + d.r)) == 0) && sign(l) != 0){
        // 内接 or 外接
        // 一つの接線
        res.push_back(a);
    }
    return res;
}

// 1点を通る円の接線( pがcの外側にあることが前提条件 )
// verified : AOJ 2579
vector<L> tangents_through_point(const C& c, const P& p){
    vector<L> tangents;
    double d = abs(c.p - p);
    // d ^ 2 == r ^ 2 + e ^ 2
    double e = sqrt(d * d - c.r * c.r); // 点pと円の接点の距離
    // d * sin(th) = r
    double th = asin(c.r / d);
    P q1 = p + (c.p - p) * polar(1.0, +th) * e / d;
    P q2 = p + (c.p - p) * polar(1.0, -th) * e / d;
    tangents.push_back({p, q1});
    tangents.push_back({p, q2});
    return tangents;
}
