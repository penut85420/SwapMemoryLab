# Swap Memory 小實驗

## 介紹
+ 觀察並使用 Swap Memory

## 環境
+ Ubuntu
    + `sudo apt install gcc make valgrind`
+ 設定 `overcommit_memory` 以讓 OOM Malloc 可以正常運作
    + `sudo bash -c 'echo 2 > /proc/sys/vm/overcommit_memory'`
    + 結束實驗之後再改回來
        + `sudo bash -c 'echo 0 > /proc/sys/vm/overcommit_memory'`
    + 關於 Overcommit 可以參考[這篇文章](https://serverfault.com/a/606193)

## 警告
+ 執行本實驗期間，將會大幅降低電腦的運算速度

## 使用方法
+ 在沒有增加 Swap Memory 的情況下執行 `make all`
    + 在 RAM 不足的情況下，會看到類似以下的輸出
        ```
        Allocate 1GB at 0x4a51030
        Init (1/1) [====================]
        Allocate 2GB at 0x58c45030
        Init (2/2) [====================]
        Allocate 3GB at (nil)
        Allocate 4GB at (nil)
        Allocate 5GB at (nil)
        (...Skip)
        ```
    + 出現 `(nil)` 表示記憶體不足無法配置
+ 增加 Swap Memory 執行 `sudo make swap`
    + 新增完 Swap 之後再次執行 `make all` 輸出有所改變
        ```
        Allocate 1GB at 0x4a51030
        Init (1/1) [====================]
        Allocate 2GB at 0x58c45030
        Init (2/2) [====================]
        Allocate 3GB at 0x58c45030
        Init (3/3) [====================]
        Allocate 4GB at 0x58c45030
        Init (4/4) [====================]
        Allocate 5GB at 0x58c45030
        Init (5/5) [====================]
        Allocate 6GB at 0x58c45030
        Init (6/6) [====================]
        Allocate 7GB at 0x58c45030
        Init (7/7) [====================]
        Allocate 8GB at 0x58c45030
        Init (8/8) [====================]
        (...Skip)
        ```
    + 可以配置的記憶體變多了
    + 可以觀察到在 Init 在超過主記憶體上限之後執行速度明顯變慢
    + 輸入 `free -h` 可以觀察記憶體的使用量
+ 可開啟 `memory.log` 觀察 Memory Usage
+ 清除 Swap 與測試檔案
    + `sudo make swapoff && make clean`
