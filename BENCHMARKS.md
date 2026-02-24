# Quant Simulator Performance Benchmarks

**Hardware:** Apple Silicon (M-Series)
**Event Count:** 1,000,000 simulated limit orders

| Date | Version / Architecture | Build Type | Run 1 | Run 2 | Run 3 | Average |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Feb 24 | v1.0 - `std::map` OrderBook | Debug | 847k µs | 851k µs | 849k µs | **~857,000 µs** |
| Feb 24 | v1.0 - `std::map` OrderBook | Release (-O3 -native) | 128k µs | 125k µs | 125k µs | **~126,000 µs** |

*Note: The Release build achieved a 6.8x speedup, processing ~8,000,000 events per second.*