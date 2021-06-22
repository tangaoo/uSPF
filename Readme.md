## uSPF

* uSPF(Micro Subscribe Publish Frame)是一个轻量级**发布-订阅**模式的框架，适合嵌入式应用。 

## 编译

```console
git clone https://github.com/tangaoo/uSPF.git

cd uSPF

make
```

## 接口

#### 定义 

```c++
USPF_MSG_DEFINE(demo_topic, sizeof(demo_data_t));
```

#### 注册

```c++
uspf_register(USPF_MSG_ID(demo_topic), NULL);
```

#### 订阅

```c++
uspf_node_ref_t node = uspf_subscribe(USPF_MSG_ID(demo_topic), 0, NULL);
```
* 注册同时可以传一个回调函数，该回调函数会在发布模块中被执行。
* 如果需要**同步轮询**，需要定义event。

#### 发布

```c++
uspf_publish(USPF_MSG_ID(demo_topic), &data);
```

#### 轮询（同步/非同步）

```c++
uspf_poll(node);
uspf_poll_sync(node);
```

#### 获取数据

```c++
uspf_copy(USPF_MSG_ID(demo_topic), node, &data);
```

#### 补充

* publish 代码与 subscribe 代码分属不同文件时，一般定义 topic 放在 publish 部分，而声名放在 subscribe 部分。

* 详细部分参见example。

## TODO

* [ ] 目前仅支持数据包形式topic订阅，后续需要支持纯流数据的支持;
* [ ] 目前仅支持单进程内部订阅与发布，后续需支持多进程。