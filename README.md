# Modify_Prometheus
1、将rc_control.cpp放在/home/amov/Prometheus/Modules/control/src/Utilities此路径下，添加cmake依赖

add_executable(rc_control src/Utilities/rc_control.cpp)

add_dependencies(rc_control prometheus_control_gencpp)

target_link_libraries(rc_control ${catkin_LIBRARIES})add_dependencies

然后直接编译，此步骤实现遥控器通道控制无人机运动

2、将px4_pos_estimator.cpp替换成这个，然后进行编译，这个步骤实现室外时高度来源应用tfmini传感器的数据，前提是将tfmini接口利用ttl转usb的接口插在板载中

3、将px4_sender.cpp替换成这个，然后进行编译，此cpp文件目的是测试控制算法，相比之前添加了误差，也就是ref-rel便于分析，方法：利用博客写的记录话题方法分析

4、增加3dlidar_plugin,将文件放置/opt/ros/melodic/lib路径下，运行roslaunch prometheus_gazebo sitl_astar_3dlidar.launch就可正常运行

