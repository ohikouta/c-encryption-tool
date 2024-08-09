# ベースイメージとして最新のAlpine Linuxを使用
FROM alpine:latest

# 必要なパッケージのインストール
RUN apk add --no-cache gcc musl-dev

# 作業ディレクトリの設定
WORKDIR /app

# ソースコードをコンテナ内にコピー
COPY main.c .

# プログラムのビルド
RUN gcc -o encrypt_tool main.c

# 入力ファイルをマウントするためのディレクトリを作成
VOLUME ["/data"]

# デフォルトの実行コマンド（コンテナ起動時に上書き可能）
CMD ["/app/encrypt_tool"]
