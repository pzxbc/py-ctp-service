## py-ctp-service

基于`pybind11`库对`CTP`进行的`Python`绑定

## 依赖
1. `pybind11`
2. `boost`
3. `cmake`


## 编译生成
```shell
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cmake --build . -j 4
```

> 建议使用`clang`编译生成，提示的错误更准确。

## 调试

1. 查看当前与ctp_front是否有网络数据
```
sudo tcpdump -i eth_name host ip_for_ctp_front -vv
```

2. 使用iptables中断与ctp_front的连接，测试断网处理

