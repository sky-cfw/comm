/*
 * @Author: your name
 * @Date: 2022-01-15 23:18:16
 * @LastEditTime: 2022-02-08 14:07:08
 * @LastEditors: Please set LastEditors
 * @Description: tcp监听服务器
 * @FilePath: /comm/linux/network/tcp_server.go
 */
package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"runtime"
	"time"
	// log "github.com/sirupsen/logrus"
)

// func init() {
// 	// Log as JSON instead of the default ASCII formatter.
// 	log.SetFormatter(&log.JSONFormatter{})

// 	// Output to stdout instead of the default stderr
// 	// Can be any io.Writer, see below for File example
// 	log.SetOutput(os.Stdout)

// 	// Only log the warning severity or above.
// 	log.SetLevel(log.WarnLevel)
// }
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
	fmt.Println(runtime.Version())
	argc := len(os.Args)
	if argc < 2 {
		fmt.Println("usage: ./tcp_server <port>")
		return
	}

	//
	addr := ":" + os.Args[1]
	// fmt.Println("starting the server")
	log.Println("starting the server")
	ls, err := net.Listen("tcp", addr)
	if err != nil {
		//fmt.Println("err listen", err.Error())
		log.Println("err listen", err.Error())
		return
	}

	cnt := 0 //短变量声明
	start := time.Now()
	for {
		_, err := ls.Accept()
		if err != nil {
			log.Println("err accept", err.Error())
			log.Println("recv conn total num", cnt)
			return
		}

		cnt++
		if 0 == cnt%10 {
			cost := time.Since(start)
			log.Printf("conn num [%d], cost [%s]", cnt, cost)
			start = time.Now()
		}
	}
}
