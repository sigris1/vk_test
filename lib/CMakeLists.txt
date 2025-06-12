add_library(metrics_controller
        Metrics/DefaultMetric.h
        MetricsWriters/FileWriter.cpp
        MetricsWriters/FileWriter.h
        MetricsWriters/Writer.h
        ResultsAnalyzer/ResultAnalyzer.h
        MetricsManager/MetricsManager.h
        MetricsManager/MetricsManager.cpp
        MetricsManager/MetricsManager.h
)

target_include_directories(metrics_controller PUBLIC "${PROJECT_SOURCE_DIR}/include")
