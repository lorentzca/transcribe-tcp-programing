#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  struct sockaddr_in server;
  int sock;
  char buf[32];
  int n;

  /* ソケットの作成 */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* 接続先指定用構造体の準備 */
  server.sin_family = AF_INET;
  server.sin_port = htons(11111);
  server.sin_len = sizeof(server);
  /* ↑linuxでは不要 */

  /* 127.0.0.1はlocalhost */
  inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

  /* socketaddr_in構造体の長さを設定 */
  /* (linuxでは不要) */
  server.sin_len = sizeof(server);

  /* サーバに接続 */
  connect(sock, (struct sockaddr *)&server, sizeof(server));

  /* サーバからデータを受信 */
  memset(buf, 0, sizeof(buf));
  n = read(sock, buf, sizeof(buf));

  printf("%d, %s\n", n, buf);

  /* socketの終了 */
  close(sock);

  return 0;
}
