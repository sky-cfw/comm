/*
 * @Author: your name
 * @Date: 2022-01-15 23:18:16
 * @LastEditTime: 2022-02-07 23:19:00
 * @LastEditors: Please set LastEditors
 * @Description: tcp监听服务器
 * @FilePath: /comm/linux/network/tcp_server.go
 */
package main

import (
	"fmt"
	"net"
	"os"
	"runtime"
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

func main() {
	fmt.Println(runtime.Version())
	argc := len(os.Args)
	if argc < 2 {
		fmt.Println("usage: ./tcp_server <port>")
		return
	}

	//
	fmt.Println("starting the server")
	addr := ":" + os.Args[1]
	ls, err := net.Listen("tcp", addr)
	if err != nil {
		fmt.Println("err listen", err.Error())
		return
	}

	cnt := 0 //短变量声明

	for {
		_, err := ls.Accept()
		if err != nil {
			fmt.Println("err accept", err.Error())
			fmt.Println("recv conn total num", cnt)
			return
		}

		cnt++
		fmt.Println("conn num", cnt)
	}
}
