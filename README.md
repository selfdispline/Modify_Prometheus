# Modify_Prometheus
放在/home/amov/Prometheus/Modules/control/src/Utilities此路径下，添加cmake依赖
add_executable(rc_control src/Utilities/rc_control.cpp)
add_dependencies(rc_control prometheus_control_gencpp)
target_link_libraries(rc_control ${catkin_LIBRARIES})
然后直接编译
