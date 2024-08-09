#include <stdio.h>
#include <stdlib.h>

void encrypt_decrypt(const char *input_file, const char *output_file, const char *key) {
    FILE *ifp = fopen(input_file, "rb");
    if (ifp == NULL) {
        perror("入力ファイルを開けません");
        exit(EXIT_FAILURE);
    }

    FILE *ofp = fopen(output_file, "wb");
    if (ofp == NULL) {
        perror("出力ファイルを作成できません");
        fclose(ifp);
        exit(EXIT_FAILURE);
    }

    size_t key_len = strlen(key);
    size_t i = 0;
    int ch;

    while ((ch = fgetc(ifp)) != EOF) {
        fputc(ch ^ key[i % key_len], ofp);
        i++;
    }

    fclose(ifp);
    fclose(ofp);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("使い方: %s [e/d] 入力ファイル 出力ファイル キー\n", argv[0]);
        printf("e: 暗号化, d: 復号化\n");
        return EXIT_FAILURE;
    }

    char mode = argv[1][0];
    const char *input_file = argv[2];
    const char *output_file = argv[3];
    const char *key = argv[4];

    if (mode != 'e' && mode != 'd') {
        printf("モードは 'e'（暗号化）または 'd'（復号化）を指定してください。\n");
        return EXIT_FAILURE;
    }

    encrypt_decrypt(input_file, output_file, key);

    printf("処理が完了しました。\n");
    return EXIT_SUCCESS;
}
