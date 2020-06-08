#pragma once

#include <iostream>
#include <iomanip>  // std::setprecision
#include <deque>
#include "exprtk.hpp"
#include "termcolor.hpp"
#include <Eigen/Dense>

typedef std::vector<Eigen::Vector3d> Polyhedron_Std;
typedef std::vector<Polyhedron_Std> ConvexHullsOfCurve_Std;
typedef std::vector<ConvexHullsOfCurve_Std> ConvexHullsOfCurves_Std;

namespace faster_types
{
typedef std::pair<Eigen::Vector3d, Eigen::Vector3d> Edge;
typedef std::vector<Edge> Edges;

}  // namespace faster_types

// TODO: move this to a class (so that no one can modify these matrices)
struct basisConverter
{
  Eigen::Matrix<double, 4, 4> M_pos_bs2mv_seg0, M_pos_bs2mv_seg1, M_pos_bs2mv_rest, M_pos_bs2mv_seg_last2,
      M_pos_bs2mv_seg_last;

  Eigen::Matrix<double, 4, 4> M_pos_bs2be_seg0, M_pos_bs2be_seg1, M_pos_bs2be_rest, M_pos_bs2be_seg_last2,
      M_pos_bs2be_seg_last;

  Eigen::Matrix<double, 3, 3> M_vel_bs2mv_seg0, M_vel_bs2mv_rest, M_vel_bs2mv_seg_last;
  Eigen::Matrix<double, 3, 3> M_vel_bs2be_seg0, M_vel_bs2be_rest, M_vel_bs2be_seg_last;

  basisConverter()
  {
    // See matlab.
    // This is for t \in [0 1];

    // clang-format off

        //////BSPLINE to MINVO POSITION/////////

        M_pos_bs2mv_seg0 <<

            1.1023,    0.3421,   -0.0927,   -0.0320,
           -0.0497,    0.6578,    0.5305,    0.2118,
           -0.0473,    0.0156,    0.5052,    0.6365,
           -0.0053,   -0.0155,    0.0570,    0.1837;

        M_pos_bs2mv_seg1 <<

            0.2756,    0.0855,   -0.0232,   -0.0080,
            0.6099,    0.6381,    0.2996,    0.1225,
            0.1199,    0.2919,    0.6666,    0.7018,
           -0.0053,   -0.0155,    0.0570,    0.1837;

        M_pos_bs2mv_rest <<

            0.1837,    0.0570,   -0.0155,   -0.0053,
            0.7018,    0.6666,    0.2919,    0.1199,
            0.1199,    0.2919,    0.6666,    0.7018,
           -0.0053,   -0.0155,    0.0570,    0.1837;


        M_pos_bs2mv_seg_last2 <<

            0.1837,    0.0570,   -0.0155,   -0.0053,
            0.7018,    0.6666,    0.2919,    0.1199,
            0.1225,    0.2996,    0.6381,    0.6099,
           -0.0080,   -0.0232,    0.0855,    0.2756;

        M_pos_bs2mv_seg_last <<

            0.1837,    0.0570,   -0.0155,   -0.0053,
            0.6365,    0.5052,    0.0156,   -0.0473,
            0.2118,    0.5305,    0.6578,   -0.0497,
           -0.0320,   -0.0927,    0.3421,    1.1023;

        //////BSPLINE to BEZIER POSITION/////////

        M_pos_bs2be_seg0 <<

            1.0000,    0.0000,   -0.0000,         0,
                 0,    1.0000,    0.5000,    0.2500,
                 0,   -0.0000,    0.5000,    0.5833,
                 0,         0,         0,    0.1667;

        M_pos_bs2be_seg1 <<

            0.2500,    0.0000,   -0.0000,         0,
            0.5833,    0.6667,    0.3333,    0.1667,
            0.1667,    0.3333,    0.6667,    0.6667,
                 0,         0,         0,    0.1667;

        M_pos_bs2be_rest <<

            0.1667,    0.0000,         0,         0,
            0.6667,    0.6667,    0.3333,    0.1667,
            0.1667,    0.3333,    0.6667,    0.6667,
                 0,         0,         0,    0.1667;

        M_pos_bs2be_seg_last2 <<

            0.1667,         0,   -0.0000,         0,
            0.6667,    0.6667,    0.3333,    0.1667,
            0.1667,    0.3333,    0.6667,    0.5833,
                 0,         0,         0,    0.2500;

        M_pos_bs2be_seg_last <<

            0.1667,    0.0000,         0,         0,
            0.5833,    0.5000,         0,         0,
            0.2500,    0.5000,    1.0000,         0,
                 0,         0,         0,    1.0000;

        /////BSPLINE to MINVO VELOCITY
        M_vel_bs2mv_seg0 <<

          1.0773,    0.1667,   -0.0774,
         -0.0387,    0.7500,    0.5387,
         -0.0387,    0.0833,    0.5387;

        M_vel_bs2mv_rest <<

            0.5387,    0.0833,   -0.0387,
            0.5000,    0.8333,    0.5000,
           -0.0387,    0.0833,    0.5387;

        M_vel_bs2mv_seg_last <<

            0.5387,    0.0833,   -0.0387,
            0.5387,    0.7500,   -0.0387,
           -0.0773,    0.1667,    1.0773;

      /////BSPLINE to BEZIER VELOCITY
        M_vel_bs2be_seg0 <<

            1.0000,         0,         0,
                 0,    1.0000,    0.5000,
                 0,         0,    0.5000;

        M_vel_bs2be_rest <<

            0.5000,         0,         0,
            0.5000,    1.0000,    0.5000,
                 0,         0,    0.5000;

        M_vel_bs2be_seg_last <<

            0.5000,         0,         0,
            0.5000,    1.0000,         0,
                 0,         0,    1.0000;

    // clang-format on
  }

  //////BSPLINE to MINVO POSITION/////////
  std::vector<Eigen::Matrix<double, 4, 4>> getMinvoPosConverters(int num_pol)
  {
    std::vector<Eigen::Matrix<double, 4, 4>> M_pos_bs2mv;  // will have as many elements as num_pol
    M_pos_bs2mv.push_back(M_pos_bs2mv_seg0);
    M_pos_bs2mv.push_back(M_pos_bs2mv_seg1);
    for (int i = 0; i < (num_pol - 4); i++)
    {
      M_pos_bs2mv.push_back(M_pos_bs2mv_rest);
    }
    M_pos_bs2mv.push_back(M_pos_bs2mv_seg_last2);
    M_pos_bs2mv.push_back(M_pos_bs2mv_seg_last);
    return M_pos_bs2mv;
  }

  //////BSPLINE to BEZIER POSITION/////////
  std::vector<Eigen::Matrix<double, 4, 4>> getBezierPosConverters(int num_pol)
  {
    std::vector<Eigen::Matrix<double, 4, 4>> M_pos_bs2be;  // will have as many elements as num_pol
    M_pos_bs2be.push_back(M_pos_bs2be_seg0);
    M_pos_bs2be.push_back(M_pos_bs2be_seg1);
    for (int i = 0; i < (num_pol - 4); i++)
    {
      M_pos_bs2be.push_back(M_pos_bs2be_rest);
    }
    M_pos_bs2be.push_back(M_pos_bs2be_seg_last2);
    M_pos_bs2be.push_back(M_pos_bs2be_seg_last);
    return M_pos_bs2be;
  }

  //////BSPLINE to BSPLINE POSITION/////////
  std::vector<Eigen::Matrix<double, 4, 4>> getBSplinePosConverters(int num_pol)
  {
    std::vector<Eigen::Matrix<double, 4, 4>> M_pos_bs2bs;  // will have as many elements as num_pol
    for (int i = 0; i < num_pol; i++)
    {
      M_pos_bs2bs.push_back(Eigen::Matrix<double, 4, 4>::Identity());
    }
    return M_pos_bs2bs;
  }

  //////BSPLINE to MINVO Velocity/////////
  std::vector<Eigen::Matrix<double, 3, 3>> getMinvoVelConverters(int num_pol)
  {
    std::vector<Eigen::Matrix<double, 3, 3>> M_vel_bs2mv;  // will have as many elements as num_pol
    M_vel_bs2mv.push_back(M_vel_bs2mv_seg0);
    for (int i = 0; i < (num_pol - 2 - 1); i++)
    {
      M_vel_bs2mv.push_back(M_vel_bs2mv_rest);
    }
    M_vel_bs2mv.push_back(M_vel_bs2mv_seg_last);
    return M_vel_bs2mv;
  }

  //////BSPLINE to BEZIER Velocity/////////
  std::vector<Eigen::Matrix<double, 3, 3>> getBezierVelConverters(int num_pol)
  {
    std::vector<Eigen::Matrix<double, 3, 3>> M_vel_bs2be;  // will have as many elements as segments
    M_vel_bs2be.push_back(M_vel_bs2be_seg0);
    for (int i = 0; i < (num_pol - 2 - 1); i++)
    {
      M_vel_bs2be.push_back(M_vel_bs2be_rest);
    }
    M_vel_bs2be.push_back(M_vel_bs2be_seg_last);
    return M_vel_bs2be;
  }

  //////BSPLINE to BSPLINE Velocity/////////
  std::vector<Eigen::Matrix<double, 3, 3>> getBSplineVelConverters(int num_pol)
  {
    std::vector<Eigen::Matrix<double, 3, 3>> M_vel_bs2bs;  // will have as many elements as num_pol
    for (int i = 0; i < num_pol; i++)
    {
      M_vel_bs2bs.push_back(Eigen::Matrix<double, 3, 3>::Identity());
    }
    return M_vel_bs2bs;
  }
};

struct dynTraj
{
  std::vector<std::string> function;
  Eigen::Vector3d bbox;
  int id;
  double time_received;  // time at which this trajectory was received from an agent
  bool is_agent;         // true for a trajectory of an agent, false for an obstacle
};

struct dynTrajCompiled
{
  std::vector<exprtk::expression<double>> function;
  Eigen::Vector3d bbox;
  int id;
  double time_received;  // time at which this trajectory was received from an agent
  bool is_agent;         // true for a trajectory of an agent, false for an obstacle
  bool is_static;
};

struct polytope
{
  Eigen::MatrixXd A;
  Eigen::MatrixXd b;
};

struct PieceWisePol
{
  // Interval 0: t\in[t0, t1)
  // Interval 1: t\in[t1, t2)
  // Interval 2: t\in[t2, t3)
  //...
  // Interval n-1: t\in[tn, tn+1)

  // n intervals in total

  // times has n+1 elements
  std::vector<double> times;  // [t0,t1,t2,...,tn+1]

  // coefficients has n elements
  // The coeffients are such that pol(t)=coeff_of_that_interval*[u^3 u^2 u 1]
  // with u=(t-t_min_that_interval)/(t_max_that_interval- t_min_that_interval)
  std::vector<Eigen::Matrix<double, 4, 1>> coeff_x;  // [a b c d]' of Int0 , [a b c d]' of Int1,...
  std::vector<Eigen::Matrix<double, 4, 1>> coeff_y;  // [a b c d]' of Int0 , [a b c d]' of Int1,...
  std::vector<Eigen::Matrix<double, 4, 1>> coeff_z;  // [a b c d]' of Int0 , [a b c d]' of Int1,...

  void clear()
  {
    times.clear();
    coeff_x.clear();
    coeff_y.clear();
    coeff_z.clear();
  }

  Eigen::Vector3d eval(double t)
  {
    Eigen::Vector3d result;

    if (t >= times[times.size() - 1])
    {  // return the last value of the polynomial in the last interval
      Eigen::Matrix<double, 4, 1> tmp;
      double u = 1;
      tmp << u * u * u, u * u, u, 1.0;
      result.x() = coeff_x.back().transpose() * tmp;
      result.y() = coeff_y.back().transpose() * tmp;
      result.z() = coeff_z.back().transpose() * tmp;
      return result;
    }
    if (t < times[0])
    {  // return the first value of the polynomial in the first interval
      Eigen::Matrix<double, 4, 1> tmp;
      double u = 0;
      tmp << u * u * u, u * u, u, 1.0;
      result.x() = coeff_x.front().transpose() * tmp;
      result.y() = coeff_y.front().transpose() * tmp;
      result.z() = coeff_z.front().transpose() * tmp;
      return result;
    }
    //(times - 1) is the number of intervals
    for (int i = 0; i < (times.size() - 1); i++)
    {
      if (times[i] <= t && t < times[i + 1])
      {
        double u = (t - times[i]) / (times[i + 1] - times[i]);

        // TODO: This is hand-coded for a third-degree polynomial
        Eigen::Matrix<double, 4, 1> tmp;
        tmp << u * u * u, u * u, u, 1.0;

        result.x() = coeff_x[i].transpose() * tmp;
        result.y() = coeff_y[i].transpose() * tmp;
        result.z() = coeff_z[i].transpose() * tmp;

        break;
      }
    }
    return result;
  }

  void print()
  {
    std::cout << "coeff_x.size()= " << coeff_x.size() << std::endl;
    std::cout << "times.size()= " << times.size() << std::endl;

    for (int i = 0; i < (times.size() - 1); i++)
    {
      std::cout << "From " << times[i] << " to " << times[i + 1] << std::endl;
      std::cout << "  Coeff_x= " << coeff_x[i].transpose() << std::endl;
      std::cout << "  Coeff_y= " << coeff_y[i].transpose() << std::endl;
      std::cout << "  Coeff_z= " << coeff_z[i].transpose() << std::endl;
    }
  }
};

struct PieceWisePolWithInfo
{
  PieceWisePol pwp;

  Eigen::Vector3d bbox;
  int id;
  double time_received;  // time at which this trajectory was received from an agent
  bool is_agent;         // true for a trajectory of an agent, false for an obstacle
  bool is_static;
};

struct parameters
{
  bool use_ff;
  bool visual;

  double dc;
  double goal_radius;
  double drone_radius;

  int N_whole;
  int N_safe;

  double Ra;

  double w_max;
  double alpha_filter_dyaw;

  bool impose_fov = false;

  double fov_horiz_deg = 60;  //[deg] angle between two faces of the tetrahedron
  double fov_vert_deg = 60;   //[deg] angle between two faces of the tetrahedron
  double fov_depth = 3.0;

  double R_local_map;

  double z_ground;
  double z_max;

  Eigen::Vector3d v_max;
  Eigen::Vector3d a_max;
  Eigen::Vector3d j_max;

  double alpha;

  int num_pol;
  int deg_pol;
  int samples_per_interval;
  double weight;
  double epsilon_tol_constraints;
  double xtol_rel;
  double ftol_rel;
  std::string solver;

  double upper_bound_runtime_snlopt;
  double kappa;
  double mu;

  int a_star_samp_x = 7;
  int a_star_samp_y = 7;
  int a_star_samp_z = 7;
  double a_star_fraction_voxel_size = 0.5;
  bool allow_infeasible_guess = false;

  double a_star_bias = 1.0;

  std::string basis;

  double res_plot_traj;

  double factor_v_max = 0.6;

  double beta = 1.0;
  double gamma = 0.0;
};

struct state
{
  Eigen::Vector3d pos = Eigen::Vector3d::Zero();
  Eigen::Vector3d vel = Eigen::Vector3d::Zero();
  Eigen::Vector3d accel = Eigen::Vector3d::Zero();
  Eigen::Vector3d jerk = Eigen::Vector3d::Zero();

  double yaw = 0;
  double dyaw = 0;

  void setPos(const double x, const double y, const double z)
  {
    pos << x, y, z;
  }
  void setVel(const double x, const double y, const double z)
  {
    vel << x, y, z;
  }
  void setAccel(const double x, const double y, const double z)
  {
    accel << x, y, z;
  }

  void setJerk(const double x, const double y, const double z)
  {
    jerk << x, y, z;
  }

  void setPos(const Eigen::Vector3d& data)
  {
    pos << data.x(), data.y(), data.z();
  }

  void setVel(const Eigen::Vector3d& data)
  {
    vel << data.x(), data.y(), data.z();
  }

  void setAccel(const Eigen::Vector3d& data)
  {
    accel << data.x(), data.y(), data.z();
  }

  void setJerk(const Eigen::Vector3d& data)
  {
    jerk << data.x(), data.y(), data.z();
  }

  void setState(const Eigen::Matrix<double, 9, 1>& data)
  {
    pos << data(0, 0), data(1, 0), data(2, 0);
    vel << data(3, 0), data(4, 0), data(5, 0);
    accel << data(6, 0), data(7, 0), data(8, 0);
  }

  void setYaw(const double& data)
  {
    yaw = data;
  }
  void setZero()
  {
    pos = Eigen::Vector3d::Zero();
    vel = Eigen::Vector3d::Zero();
    accel = Eigen::Vector3d::Zero();
    jerk = Eigen::Vector3d::Zero();
    yaw = 0;
    dyaw = 0;
  }

  const void printPos()
  {
    std::cout << "Pos= " << pos.transpose() << std::endl;
  }

  const void print()
  {
    std::cout << std::setprecision(3) << "Pos= " << pos.transpose() << std::endl;
    std::cout << std::setprecision(3) << "Vel= " << vel.transpose() << std::endl;
    std::cout << std::setprecision(3) << "Accel= " << accel.transpose() << std::endl;
  }

  const void printHorizontal()
  {
    using namespace termcolor;
    std::cout << std::setprecision(3) << "Pos, Vel, Accel, Jerk= " << red << pos.transpose() << reset;
    std::cout << " " << std::setprecision(3) << blue << vel.transpose() << reset;
    std::cout << " " << std::setprecision(3) << green << accel.transpose() << reset;
    std::cout << " " << std::setprecision(3) << jerk.transpose() << std::endl;
  }
};

typedef std::vector<state> trajectory;

struct committedTrajectory
{
  std::deque<state> content;

  void print()
  {
    for (auto state_i : content)
    {
      state_i.printHorizontal();
    }
  }

  // now define the functions operating on the member of this struct directly
  int size()
  {
    return content.size();
  }

  void push_back(state tmp)
  {
    content.push_back(tmp);
  }

  void erase(std::deque<state>::iterator a, std::deque<state>::iterator b)
  {
    content.erase(a, b);
  }

  state front()
  {
    return content.front();
  }

  state back()
  {
    return content.back();
  }

  void pop_front()
  {
    content.pop_front();
  }

  std::deque<state>::iterator end()
  {
    return content.end();
  }

  std::deque<state>::iterator begin()
  {
    return content.begin();
  }

  state get(int i)
  {
    return content[i];
  }

  std::vector<state> toStdVector()
  {
    std::vector<state> my_vector;
    std::copy(content.begin(), content.end(), std::back_inserter(my_vector));
    return my_vector;
  }
};