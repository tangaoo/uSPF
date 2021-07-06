## uSPF

* uSPF(Micro Subscribe Publish Frame)是一个轻量级**发布-订阅**模式的框架，甚至没有 broker(代理)，特别适合嵌入式应用，详细文档见[uSPF微型框架的介绍](https://tangaoo.github.io/2021/07/05/uSPF/)。

## 编译

* uSPF 库 引用了 [ttlib_mirco](https://github.com/tangaoo/ttlib_micro)，所以需要 **--recursive** 后缀。

```console
git clone https://github.com/tangaoo/uSPF.git --recursive

cd uSPF

make
```

## 依赖

* uSPF 框架依赖 [ttlib_mirco](https://github.com/tangaoo/ttlib_micro)库(即工程中dep目录)，具体可见项目主页。

## 用法

#### 定义 

```c++
typedef struct __demo_data_t
{
    const char* name;
    int a;
}demo_data_t, *demo_data_ref_t;

USPF_MSG_DEFINE(demo_topic, sizeof(demo_data_t));
```

#### 注册

```c++
uspf_register(USPF_MSG_ID(demo_topic), NULL);
```

#### 订阅

* 异步注册，poll 时不会阻塞。

```c++
uspf_node_ref_t node = uspf_subscribe(USPF_MSG_ID(demo_topic), USPF_ASYNC, tt_null);
```

* 同步注册，poll 时会阻塞。

```c++
uspf_node_ref_t node = uspf_subscribe(USPF_MSG_ID(demo_topic), USPF_SYNC, tt_null);
```

#### 发布

```c++
uspf_publish(USPF_MSG_ID(demo_topic), &data);
```

#### 轮询（同步/非同步）

* 异步轮询，非阻塞。

```c++
uspf_poll(node);
```

* 同步轮询，阻塞。

```c++
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

* [x] 引入 ttlib_mirco 库，替换目前的链表操作;
* [ ] 目前仅支持数据包形式topic订阅，后续需要支持纯流数据的支持;
* [ ] 目前仅支持单进程内部订阅与发布，后续需支持多进程。