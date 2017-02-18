#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socklen_t len;
  int sock1, sock2;

  /* ソケットの作成 */
  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  /*** ソケットの設定 ***/

  /* IPv4を使うことを指定 */
  addr.sin_family = AF_INET;

  /* ポート番号は11111 */
  addr.sin_family = AF_INET;

  /* 任意のインターフェースを設定 */
  addr.sin_addr.s_addr = INADDR_ANY;

  /* ソケットをインターフェースとポートに関連付け */
  bind(sock0, (struct socketaddr *)&addr, sizeof(addr));

  /* TCPクライアントからの接続要求を待てるようにする */
  listen(sock0, 5);

  /* TCPクライアントからの接続要求を受け付ける(1回目) */
  len = sizeof(client);
  sock1 = accept(sock0, (struct sockaddr *)&client, &len);

  /* 6文字送信 */
  /* ('H', 'E', 'L', 'L', 'O', '\0') */
  write(sock1, "HELLO", 6);

  /* TCPセッション1の終了 */
  close(sock1);

  /* TCPクライアントからの接続要求を受け付ける(2回目) */
  len = sizeof(client);
  sock2 = accept(sock0, (struct sockaddr *)&client, &len);

  /* 5文字送信 */
  /* ('H', 'O', 'G', 'E', '\0') */
  write(sock2, "HOGE", 5);

  /* TCPセッション2の終了 */
  close(sock2);

  /* listenするsocketの終了 */
  close(sock0);

  return 0;
}
