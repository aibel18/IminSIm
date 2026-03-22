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

vec3 acceleration(int angle, int power, vec3 gravity) {
  constexpr float fact_to_radiam = 3.1416f / 180;
  float angle_radian = angle * fact_to_radiam;
  return gravity + vec3{-sin(angle_radian) * power, cos(angle_radian) * power, 0.0f}; 
}

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

      float B = 1;
      float m = ((float)(p.y - ini_p.y)) / (p.x - ini_p.x);
      float A = -m;
      float C = m * ini_p.x - ini_p.y;

      float B2 = 1;
      float m2 = ((float)(goal.y - p.y)) / (goal.x - p.x);
      float A2 = -m2;
      float C2 = m2 * p.x - p.y;

      int collision = 0, collision2 = 0;
      for (auto s : *surface) {
        float p1 = s.x1 * A + s.y1 * B + C;
        float p2 = s.x2 * A + s.y2 * B + C;

        float p12 = s.x1 * A2 + s.y1 * B2 + C2;
        float p22 = s.x2 * A2 + s.y2 * B2 + C2;

        if (p1 * p2 < 0) {
          collision++;
        }
        if (p12 * p22 < 0) {
          collision2++;
        }
      }
      auto dist = norm(p - goal);
      // TODO: improve the velocity contraint
      // float fact_v_x = abs(v.x) < 18 ? 0 : v.x * v.x * 0.5;
      // float fact_v_y = abs(v.y) < 40 ? 0 : v.y * v.y * 0.25;
      // float velocityConstraint = fact_v_x + fact_v_y;
      float velocityConstraint = v.x * v.x * 0.28 + v.y * v.y * 0.26;
      double error = dist * 2.0 + collision * 100000 + collision2 * 50000 + velocityConstraint;
      if (minError > error) {
        minError = error;
        angle = r;
        power = pow;
      }
    }
  }
  time = logistical(minError);
  // LOG_DEBUG("error: %f -> time: %i", minError, time);

  return Result{angle, power, time};
}

std::vector<seg> surface;
int flat_ground_i, flat_ground_f;
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
