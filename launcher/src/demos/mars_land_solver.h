struct Result {
  int angle;
  int power;
  int time;
};
struct seg {
  float x1;
  float y1;
  float x2;
  float y2;
};

int logistical(float h) {
  const float a = 1.f;
  const float b = 55.f;
  const float center = 2500.f;
  
  return floor(b + (a - b) / (1 + (h / center) * (h / center)));
}

bool interseptionOnLine(float &A, float& B, float&C, float x1, float y1, float x2, float y2) {
  float v1 = (A * x1 + B * y1 + C );
  float v2 = (A * x2 + B * y2 + C );
  return v1 * v2 <= 0;
}

// TODO: move to math folder adn 
bool rayCasting(vec3& rayOri, vec3& rayDir, vec3& segA, vec3& segB, vec3& hitPoint, float& tOut) {

  float x1 = segA.x;
  float y1 = segA.y;
  float x2 = segB.x;
  float y2 = segB.y;

  float px = rayOri.x;
  float py = rayOri.y;
  float dx = rayDir.x;
  float dy = rayDir.y;

  // Denominator of the equations
  float den = dx * (y2 - y1) - dy * (x2 - x1);

  // Parallel lines check
  if (den == 0) return false;

  // Solve for t and u
  float t = ((x1 - px) * (y2 - y1) - (y1 - py) * (x2 - x1)) / den;
  float u = ((x1 - px) * dy - (y1 - py) * dx) / den;

  // Check if the intersection is valid
  if (t >= 0 && u >= 0 && u <= 1) {
    hitPoint.x = px + t * dx;
    hitPoint.y = py + t * dy;
    tOut = t;
    return true;
  }

  return false;

}

vec3 acceleration(int angle, int power, vec3 gravity) {
  constexpr float fact_to_radiam = 3.1416f / 180;
  float angle_radian = angle * fact_to_radiam;
  return gravity + vec3{-sin(angle_radian) * power, cos(angle_radian) * power, 0.0f}; 
}
int flat_ground_i, flat_ground_f;
auto heuristic(vec3 goal, vec3 ini_p, vec3 ini_v, vec3 g, int time, std::vector<seg>* surface) {
  float minError = 10000000000.0f;
  int angle = 0;
  int power = 4;

  for (int pow = 0; pow < 5; pow++) {
    for (int r = -40; r <= 40; r += 2) {
      vec3 p, v, a;

      a = acceleration(r, pow, g);

      p = ini_p + ini_v * time + a * time * time * 0.5;

      if (p.x < 0 || p.x > 6999 || p.y < 0 || p.y > 2999)
        continue;

      v = ini_v + a * time;
      // v = (p - ini_p) / time;

      float A2 = p.y - goal.y;
      float B2 = goal.x - p.x;
      float C2 = p.x * goal.y - goal.x * p.y;

      vec3 dir = normalize( p - ini_p);

      int collision = 0, collision2 = 0;
      for (auto s : *surface) {

        vec3 s1 = {s.x1, s.y1, 0};
        vec3 s2 = {s.x2, s.y2, 0};
        vec3 hitPoint;
        float t = 0;

        if( rayCasting(ini_p, dir, s1, s2, hitPoint, t) ) {
          collision+= t;
        }

        float A3 = s.y1 - s.y2;
        float B3 = s.x2 - s.x1;
        float C3 = s.x1 * s.y2 - s.x2 * s.y1;

        // Evaluate s1 and s2 against line p,goal
        auto v2 = interseptionOnLine(A2, B2, C2, s.x1, s.y1, s.x2, s.y2);

        // Evaluate p and goal against line s1,s2
        auto v4 = interseptionOnLine(A3, B3, C3, p.x, p.y, goal.x, goal.y);

        if (v2 && v4) {
          collision2++;
        }
      }
      auto dist = p - goal;        
      float goalConstraint = norm(dist) * 2.5f;
      // TODO: improve the velocity contraint
      // float fact_v_x = abs(v.x) < 18 ? 0 : v.x * v.x * 0.5;
      // float fact_v_y = abs(v.y) < 40 ? 0 : v.y * v.y * 0.25;
      // float velocityConstraint = fact_v_x + fact_v_y;
      float velocityConstraint = v.x * v.x * 0.28 + v.y * v.y * 0.26;
      float collisionConstraint = collision * 1000 + collision2 * 10000;
      double error = goalConstraint + collisionConstraint + velocityConstraint;
      if (minError > error) {
        minError = error;
        angle = r;
        power = pow;
      }
    }
  }
  time = logistical(minError);
  LOG_INFO("t:%i \ta:%i \tp:%i \te: %f", time, angle, power, minError);

  return Result{angle, power, time};
}

std::vector<seg> surface;
vec3 goal;
void findGoal(std::vector<vec3> &points) {

  surface.clear();

  int land_y_prev = -1;
  int land_x_prev = -1;
  int flat_ground_h;

  for (int i = 0; i < points.size(); i++) {
    int land_x = points[i].x;  // X coordinate of a surface point. (0 to 6999)
    int land_y = points[i].y;  // Y coordinate of a surface point. By linking all the points

    // pre-calcute lines
    if (i > 0) {

      if (land_y_prev == land_y) {
        flat_ground_i = land_x_prev;
        flat_ground_f = land_x;
        flat_ground_h = land_y;
      } else {
        surface.push_back({(float)land_x_prev, (float)land_y_prev, (float)land_x, (float)land_y});
      }
    }
    land_y_prev = land_y;
    land_x_prev = land_x;
  }

  goal = {(flat_ground_f + flat_ground_i) * 0.5f, (float)flat_ground_h, 0.0f};

}

int t = 55; // initial time for prediction
void solve(vec3 p, vec3 v, vec3 g, int &angle, int &power) {
  // when the rocket is stable and very close to goal
  if (p.x > flat_ground_i && p.x < flat_ground_f && p.y < goal.y + 200) {
    angle = 0;
    power = v.y < -25 ? 4 : 0;
  } else {
    auto res = heuristic(goal, p, v, g, t, &surface);
    t = res.time;
    angle = res.angle;
    power = res.power;
  }
}

bool verifySolution(vec3 p, vec3 v, int angle) {

  if (p.x < flat_ground_i || p.x > flat_ground_f)
    return false;

  if (p.y > goal.y)
    return false;

  if( angle == 0 && abs(v.x) <= 20 && abs(v.y) <= 40){
    return true;
  }
  LOG_INFO("a: %i, vx: %f, vy: %f", angle, v.x, v.y);
  return false;
}
