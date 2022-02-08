/*
 * @Author: your name
 * @Date: 2022-02-07 18:53:36
 * @LastEditTime: 2022-02-08 14:08:04
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

func init() {
	//设置输出选项
	log.SetFlags(log.Lshortfile | log.LstdFlags | log.Lmicroseconds)

	//设置输出位置
	logFile, err := os.OpenFile("./tcp_client_c10k.log", os.O_CREATE|os.O_RDWR|os.O_APPEND, 0644)
	if err != nil {
		log.Panic("打开日志文件异常")
		return
	}

	log.SetOutput(logFile)
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
