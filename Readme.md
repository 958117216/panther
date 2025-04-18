# PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments #

[![PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments](./panther/imgs/four_compressed.gif)](https://www.youtube.com/watch?v=jKmyW6v73tY "PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments")      |  [![PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments](./panther/imgs/five_compressed.gif)](https://www.youtube.com/watch?v=jKmyW6v73tY "PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments") |  
:-------------------------:|:-------------------------:|
[![PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments](./panther/imgs/eight_compressed.gif)](https://www.youtube.com/watch?v=jKmyW6v73tY "PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments")       |  [![PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments](./panther/imgs/sim_compressed.gif)](https://www.youtube.com/watch?v=jKmyW6v73tY "PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments")    |  

## Citation

When using PANTHER, please cite [PANTHER: Perception-Aware Trajectory Planner in Dynamic Environments](https://arxiv.org/) ([pdf](https://arxiv.org/), [video](https://www.youtube.com/watch?v=jKmyW6v73tY)):

```bibtex
@article{tordesillas2020panther,
  title={{PANTHER}: Perception-Aware Trajectory Planner in Dynamic Environments},
  author={Tordesillas, Jesus and How, Jonathan P},
  journal={arXiv preprint},
  year={2021}
}
```

---

**If you are looking for a Planner** 

* **In Multi-Agent and Dynamic Environments, you may be interesed also in [MADER](https://github.com/mit-acl/mader)** ([pdf](https://arxiv.org/abs/2010.11061), [video](https://www.youtube.com/watch?v=aoSoiZDfxGE)):
* **In Static Unknown environments, you may be interesed also in [FASTER](https://github.com/mit-acl/faster)** ([pdf](https://arxiv.org/abs/1903.03558), [video](https://www.youtube.com/watch?v=fkkkgomkX10))

## General Setup

PANTHER has been tested with Ubuntu 18.04/ROS Melodic. Other Ubuntu/ROS version may need some minor modifications, feel free to [create an issue](https://github.com/mit-acl/panther/issues) if you have any problems.

**You can use PANTHER with only open-source packages**. 
Matlab is only needed if you want to introduce modifications to the optimization problem.

### <ins>Dependencies<ins>


#### CGAL
These commands will install [CGAL v4.12.4](https://www.cgal.org/):
```bash
sudo apt-get install libgmp3-dev libmpfr-dev -y
mkdir -p ~/installations/cgal && cd ~/installations/cgal
wget https://github.com/CGAL/cgal/releases/download/releases%2FCGAL-4.14.2/CGAL-4.14.2.tar.xz
tar -xf CGAL-4.14.2.tar.xz && cd CGAL-4.14.2/ && cmake . -DCMAKE_BUILD_TYPE=Release && sudo make install
```

#### CasADi and IPOPT

Install CasADi from source (see [this](https://github.com/casadi/casadi/wiki/InstallationLinux) for more details) and the solver IPOPT:
```bash
sudo apt-get install gcc g++ gfortran git cmake liblapack-dev pkg-config --install-recommends
sudo apt-get install swig
sudo apt-get install coinor-libipopt-dev
cd ~/installations #Or any other folder of your choice
git clone https://github.com/casadi/casadi.git -b master casadi
cd casadi && mkdir build && cd build
cmake . -DCMAKE_BUILD_TYPE=Release -DWITH_PYTHON=ON -DWITH_IPOPT=ON .. 
sudo make install
``` 

<details>
  <summary> <b>Optional (recommended for better performance)</b></summary>

To achieve better performance, you can use other linear solvers for Ipopt (instead of the default `mumps` solver). Specifically, we found that `MA27` and `MA57` are usually faster than the default `mumps` solver.

Go to [http://www.hsl.rl.ac.uk/ipopt/](http://www.hsl.rl.ac.uk/ipopt/), and then 

* If you want the solver `MA57` (or `MA27`, or both), click on `Coin-HSL Full (Stable) Source`. This is free for academia. 
* If you only want the solver `MA27`, click on `Personal Licence, Source`. This is free for everyone

And fill and submit the form. Then download the compressed file from the link of the email you receive. Uncompress that file, and place it in a folder `~/installations` (for example). Then execute the following commands:

> Note: the instructions below follow [this](https://github.com/casadi/casadi/wiki/Obtaining-HSL) closely

```bash
cd ~/installations/coinhsl-2015.06.23
wget http://glaros.dtc.umn.edu/gkhome/fetch/sw/metis/OLD/metis-4.0.3.tar.gz #This is the metis version used in the configure file of coinhsl
tar xvzf metis-4.0.3.tar.gz
#sudo make uninstall && sudo make clean #Only needed if you have installed it before
./configure LIBS="-llapack" --with-blas="-L/usr/lib -lblas" CXXFLAGS="-g -O3 -fopenmp" FCFLAGS="-g -O3 -fopenmp" CFLAGS="-g -O3 -fopenmp" #the output should say `checking for metis to compile... yes`
sudo make install #(the files will go to /usr/local/lib)
cd /usr/local/lib
sudo ln -s libcoinhsl.so libhsl.so #(This creates a symbolic link `libhsl.so` pointing to `libcoinhsl.so`). See https://github.com/casadi/casadi/issues/1437
echo "export LD_LIBRARY_PATH='\${LD_LIBRARY_PATH}:/usr/local/lib'" >> ~/.bashrc
```
</details>


<details>
  <summary> <b>Optional (only if you want to modify the optimization problem, MATLAB needed)</b></summary>

The easiest way to do this is to install casadi from binaries by simply following these commands:

````bash
cd ~/installations
mkdir casadi
wget https://github.com/casadi/casadi/releases/download/3.5.5/casadi-linux-matlabR2014b-v3.5.5.tar.gz
tar xvzf casadi-linux-matlabR2014b-v3.5.5.tar.gz -C ./casadi
````

Open Matlab, execute the command `edit(fullfile(userpath,'startup.m'))`, and add the line `addpath(genpath('/home/YOUR_USERNAME/installations/casadi'))` in that file (changing `YOUR_USERNAME` with your username). This file `startup.m` is executed every time Matlab starts.

Then you can restart Matlab (or run the file `startup.m`), and make sure this works: 

```bash
import casadi.*
x = MX.sym('x')
disp(jacobian(sin(x),x))

```

Then, to use a specific linear solver, you simply need to change the name of `linear_solver_name` in the file `main.m`, and then run that file.

> Note: When using a linear solver different from `mumps`, you need to start Matlab from the terminal (typing `matlab`).More info [in this issue](https://github.com/casadi/casadi/issues/2032).

> Note: Instead of the binary installation explained in this section, another (but not so straightforward) way would be to use the installation `from source` done above, but it requires some patches to swig, see [this](https://github.com/casadi/casadi/wiki/matlab).
</details>


### <ins>Compilation<ins>
```bash
cd ~/Desktop && mkdir ws && cd ws && mkdir src && cd src
git clone https://github.com/mit-acl/panther.git
cd panther
sudo apt-get install git-lfs #Make sure you have git-lfs installed
git lfs install
git submodule init && git submodule update
catkin build
echo "source /home/YOUR_USER/Desktop/ws/devel/setup.bash" >> ~/.bashrc 
```

### Running Simulations

Simply execute

```
roslaunch panther simulation.launch quad:=SQ01s
```

Now you can click `Start` on the GUI, and then press `G` (or click the option `2D Nav Goal` on the top bar of RVIZ) and click any goal for the drone. 


You can also change the following arguments when executing `roslaunch`

| Argument      | Description |
| ----------- | ----------- |
| `quad`      | Name of the drone        |
| `perfect_controller`      | If true, the drone will track perfectly the trajectories, and the controller and physics engine of the drone will not be launched. If false, you will need to clone and compile [snap_sim](https://gitlab.com/mit-acl/fsw/snap-stack/snap_sim), [snap](https://gitlab.com/mit-acl/fsw/snap-stack/snap) and [outer_loop](https://gitlab.com/mit-acl/fsw/snap-stack/outer_loop)       |
| `perfect_prediction`      | If true, the drone will have access to the ground truth of the trajectories of the obstacles. If false, the drone will estimate their trajectories (it needs `gazebo=true` in this case).       |
| `gui_mission`      | If true, a gui will be launched to start the experiment       |
| `rviz`      | If true, Rviz will be launched for visualization       |
| `gazebo`      | If true, Gazebo will be launched  |
| `gzclient`      | If true, the gui of Gazebo will be launched. If false, (and if `gazebo=true`) only gzserver will be launched. Note: right now there is some delay in the visualization of the drone the gui of Gazebo. But this doesn't affect the point clouds generated. |

You can see the default values of these arguments in `simulation.launch`.

> **_NOTE:_**  (TODO) Right now the radius of the drone plotted in Gazebo (which comes from the `scale` field of `quadrotor_base_urdf.xacro`) does not correspond with the radius specified in `mader.yaml`. 


## Credits:
This package uses some the [hungarian-algorithm-cpp](https://github.com/mcximing/hungarian-algorithm-cpp) and some C++ classes from the [DecompROS](https://github.com/sikang/DecompROS) and  repos (both included in the `thirdparty` folder), so credit to them as well. 

---------

> **Approval for release**: This code was approved for release by The Boeing Company in March 2021. 
