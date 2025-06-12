add_executable(Metric_controller main.cpp)

target_link_libraries(Metric_controller PRIVATE metrics_controller)
target_include_directories(Metric_controller PUBLIC ../../vk_test)