/*
 * @Author: your name
 * @Date: 2022-02-07 18:53:36
 * @LastEditTime: 2022-02-08 15:49:34
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /comm/linux/network/tcp_client_c10k.go
 */

package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"time"
)

//https://www.topgoer.com/go%E5%9F%BA%E7%A1%80/Init%E5%87%BD%E6%95%B0%E5%92%8Cmain%E5%87%BD%E6%95%B0.html
//1. go语言中init函数用于包(package)的初始化，main函数执行之前由go程序自动被调用(不能被其他函数调用)，该函数是go语言的一个重要特性。
//2. 同一个包，甚至同一个go文件中，可重复定义多个init函数。对于同一个go文件中的init函数，按声明顺序进行调用
func init() {
	//设置输出选项
	log.SetFlags(log.Lshortfile | log.LstdFlags | log.Lmicroseconds)

	//设置输出位置
	fileName := "./" + os.Args[0] + ".log"
	logFile, err := os.OpenFile(fileName, os.O_CREATE|os.O_RDWR|os.O_APPEND, 0644)
	if err != nil {
		log.Panic("打开日志文件异常")
		return
	}

	log.SetOutput(logFile)
}

func init() {
	fmt.Println("init exec order test1")
}

func init() {
	fmt.Println("init exec order test2")
}

func main() {
	argc := len(os.Args)
	if argc < 3 {
		fmt.Println("usage: ./tcp_client_c10k <ip> <port>")
		return
	}

	addr := os.Args[1] + ":" + os.Args[2]
	cnt := 0

	fmt.Println("start to conn server ...")
	log.Println("start to conn server ...")
	start := time.Now()
	for {
		_, err := net.Dial("tcp", addr)
		if err != nil {
			log.Println("Dial failed", err.Error())
			log.Println("conn total num", cnt)
			return
		}

		cnt++
		if 0 == cnt%10 {
			cost := time.Since(start)
			log.Printf("conn num [%d], time[%s]", cnt, cost)
			start = time.Now()
		}
	}
}
