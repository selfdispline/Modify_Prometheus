# Modify_Prometheus
将rc_control.cpp放在/home/amov/Prometheus/Modules/control/src/Utilities此路径下，添加cmake依赖

add_executable(rc_control src/Utilities/rc_control.cpp)

add_dependencies(rc_control prometheus_control_gencpp)

target_link_libraries(rc_control ${catkin_LIBRARIES})add_dependencies

然后直接编译，此步骤实现遥控器通道控制无人机运动

将px4_pos_estimator.cpp替换成这个，然后进行编译，这个步骤实现室外时高度来源应用tfmini传感器的数据，前提是将tf接口利用ttl转usb的接口插在板载中
