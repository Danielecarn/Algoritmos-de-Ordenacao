#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define tam_bucket 1000

typedef struct numero Numero;

struct numero{
    int dado;
    Numero *proximo_numero;
    Numero *numero_anterior;
};

Numero *inicio_lista;
Numero *final_lista;
int tamanho_lista;

typedef struct desempenho{    
    long int comparacoes_no_vetor;
    long int movimentos_no_vetor;
    float tempo_ordenar_vetor;
}DESEMPENHO;

DESEMPENHO desempenho_cocktail;
DESEMPENHO desempenho_counting;
DESEMPENHO desempenho_heap;
DESEMPENHO desempenho_radix_bucket;
DESEMPENHO desempenho_radix_counting;
DESEMPENHO desempenho_bucket;

typedef struct {
        int topo;
        int balde[tam_bucket];
}bucket;
void criar_lista();
Numero *alocar_numero(int dado);
void inserir_numero_fim_lista(int dado);
void imprimir();
void melhor_desempenho();
void troca_valor(Numero numero_atual);
int cocktail_sort();
int counting_sort();
int radix_com_counting_sort();
int radix_com_bucket();
void bubble(int v[],int tam); 
int radix_com_counting(); 
void count_Sort(int *copia_vetor,int exp);
void peneira(int *vet, int raiz, int fundo);
int heap_sort();
int bucket_sort(); 
void bubble(int v[],int tam);   
void menos_comparacoes();
void menos_movimentacoes();
void menos_tempo();

int main(){

    int tam = 50000;
   
    criar_lista();

    for(int i=0; i<tam; i++){
        int i = rand() % 50000; //0000;
        inserir_numero_fim_lista(i);
    }

    desempenho_cocktail.comparacoes_no_vetor = 0;
    desempenho_cocktail.movimentos_no_vetor = 0;
    desempenho_counting.comparacoes_no_vetor = 0;
    desempenho_counting.movimentos_no_vetor = 0;
    desempenho_heap.comparacoes_no_vetor= 0;
    desempenho_heap.movimentos_no_vetor = 0;
    desempenho_radix_bucket.comparacoes_no_vetor = 0;
    desempenho_radix_bucket.movimentos_no_vetor = 0;
    desempenho_bucket.comparacoes_no_vetor = 0;
    desempenho_bucket.movimentos_no_vetor = 0;
    desempenho_radix_counting.comparacoes_no_vetor = 0;
    desempenho_radix_counting.movimentos_no_vetor = 0;

    time_t tempo_inicial_cocktail, tempo_final_cocktail,tempo_inicial_counting, tempo_final_counting, 
    tempo_inicial_heap, tempo_final_heap, tempo_inicial_radix_bucket,tempo_final_radix_bucket,
    tempo_inicial_bucket, tempo_final_bucket,tempo_inicial_radix_counting,tempo_final_radix_counting;
    
    tempo_inicial_cocktail = time(NULL);
    cocktail_sort();
    tempo_final_cocktail = time(NULL);
    desempenho_cocktail.tempo_ordenar_vetor = difftime(tempo_final_cocktail, tempo_inicial_cocktail);
    
    tempo_inicial_counting = time(NULL);
    counting_sort();
    tempo_final_counting = time(NULL);
    desempenho_counting.tempo_ordenar_vetor = difftime(tempo_final_counting, tempo_inicial_counting);
   
    tempo_inicial_heap = time(NULL);
    heap_sort();
    tempo_final_heap = time(NULL);
    desempenho_heap.tempo_ordenar_vetor = difftime(tempo_final_heap , tempo_inicial_heap);
    
    tempo_inicial_bucket = time(NULL);
    bucket_sort();
    tempo_final_bucket = time(NULL);
    desempenho_bucket.tempo_ordenar_vetor = difftime(tempo_final_bucket, tempo_inicial_bucket);
   
    tempo_inicial_radix_counting = time(NULL);
    radix_com_counting();
    tempo_final_radix_counting = time(NULL);
    desempenho_radix_counting.tempo_ordenar_vetor = difftime(tempo_final_radix_counting,tempo_inicial_radix_counting);
    
    tempo_inicial_radix_bucket = time(NULL);
    radix_com_bucket();
    tempo_final_radix_bucket = time(NULL);
    desempenho_radix_bucket.tempo_ordenar_vetor = difftime(tempo_final_radix_bucket, tempo_inicial_radix_bucket);
    
    printf("COCKTAIL\n");
    printf("Comparações %li\n", desempenho_cocktail.comparacoes_no_vetor);
    printf("Movimentações %li\n", desempenho_cocktail.movimentos_no_vetor);
    printf("Tempo %f\n\n", desempenho_cocktail.tempo_ordenar_vetor);
    
    printf("COUNTING\n");
    printf("Comparações %li\n", desempenho_counting.comparacoes_no_vetor);
    printf("Movimentações %li\n", desempenho_counting.movimentos_no_vetor);
    printf("Tempo %f\n\n", desempenho_counting.tempo_ordenar_vetor);

    printf("HEAP\n");
    printf("Comparações %li\n", desempenho_heap.comparacoes_no_vetor);
    printf("Movimentações %li\n", desempenho_heap.movimentos_no_vetor);
    printf("Tempo %f\n\n", desempenho_heap.tempo_ordenar_vetor);
    
    printf("Bucket\n");
    printf("Comparações %li\n", desempenho_bucket.comparacoes_no_vetor);
    printf("Movimentações %li\n", desempenho_bucket.movimentos_no_vetor);
    printf("Tempo %f\n\n", desempenho_bucket.tempo_ordenar_vetor);
     
    printf("Radix com Counting\n");
    printf("Comparações %li\n", desempenho_radix_counting.comparacoes_no_vetor);
    printf("Movimentações %li\n", desempenho_radix_counting.movimentos_no_vetor);
    printf("Tempo %f\n\n", desempenho_radix_counting.tempo_ordenar_vetor);
    
    printf("Radix com Bucket\n");
    printf("Comparações %li\n", desempenho_radix_bucket.comparacoes_no_vetor);
    printf("Movimentações %li\n", desempenho_radix_bucket.movimentos_no_vetor);
    printf("Tempo %f\n\n", desempenho_radix_bucket.tempo_ordenar_vetor);

    menos_comparacoes();
    menos_movimentacoes();
    menos_tempo();

    return EXIT_SUCCESS;
}

void imprimir(){
    Numero *atual;
    atual = inicio_lista;

    while(atual){
        printf("%d\n", atual->dado);
        atual = atual->proximo_numero;
    } 
}

void criar_lista(){
    inicio_lista = NULL;
    final_lista = NULL;
    tamanho_lista = 0;
}
Numero *alocar_numero(int dado){
    Numero *novo_numero = (Numero*)malloc(sizeof(Numero));

    novo_numero->dado= dado;
    novo_numero->numero_anterior = NULL;
    novo_numero->proximo_numero = NULL;
    return novo_numero;
}
void inserir_numero_fim_lista(int dado){
    Numero *novo_numero = alocar_numero(dado);
    if(inicio_lista == NULL){
        inicio_lista = novo_numero;
        final_lista = novo_numero;
    }else{
        Numero *numero_atual;
        numero_atual = final_lista;
        novo_numero->numero_anterior = numero_atual;
        numero_atual->proximo_numero = novo_numero;
        final_lista = novo_numero;
    }
    tamanho_lista++;
}

void troca_valor(Numero numero_atual){ 
    int auxiliar = numero_atual.dado; 
    numero_atual.dado = numero_atual.proximo_numero->dado; 
    numero_atual.proximo_numero->dado = auxiliar;
} 

int cocktail_sort(){

    Numero *copia_vetor = inicio_lista;
    int list[tamanho_lista];
    for(int i = 0; i< tamanho_lista;i++){
        list[i] = 0;
    }
    for(int i = 0; i< tamanho_lista; i++){
        list[i] = copia_vetor->dado;
        
        copia_vetor= copia_vetor->proximo_numero;
    }
    int length,bottom,top, swapped,i,aux;
    length=tamanho_lista;
    bottom = 0;
    top = length - 1;
    swapped = 0; 
    while(swapped == 0 && bottom < top)//Se não houver troca de posições ou o ponteiro que
    {                                   //sobe ultrapassar o que desce, o vetor esta ordenado
        swapped = 1; 
        //Este for é a “ida” para a direita
        for(i = bottom; i < top; i = i + 1)
        {   
            desempenho_cocktail.comparacoes_no_vetor++;
            if(list[i] > list[i + 1])   //indo pra direita:testa se o próximo é maior
            {   //indo pra direita:se o proximo é maior que o atual,
                //troca as posições
                desempenho_cocktail.movimentos_no_vetor;
                aux=list[i];
                list[i]=list[i+1];
                list[i+1]=aux;
                swapped = 0;
            }
        }
        // diminui o  `top` porque o elemento com o maior valor 
        // já está na direita (atual posição top)
        top = top - 1; 
        //Este for é a “ida” para a esquerda
        for(i = top; i > bottom; i = i - 1)
        {  
            desempenho_cocktail.comparacoes_no_vetor++;
            if(list[i] < list[i - 1]) 
            {   
                desempenho_cocktail.movimentos_no_vetor++;
                aux=list[i];
                list[i]=list[i-1];
                list[i-1]=aux;
                swapped = 0;
            }
        }
        //aumenta o `bottom` porque o menor valor já está
        //na posição inicial (bottom) 
        bottom = bottom + 1;  
    }
    FILE *arquivo = fopen("cocktail.txt", "w+");
    if(arquivo == NULL){
        printf("Erro de alocação de memória no arquivo do cocktail sort");
        return EXIT_FAILURE;
    }
    for(int i= 0; i<tamanho_lista; i++){
        fprintf(arquivo,"%i, ", list[i]);
    }
    fclose(arquivo);
 }
int maior_numero(){
    int maior_numero = 0;
    Numero *numero_atual = inicio_lista;

    while(numero_atual != NULL){
        if(maior_numero < numero_atual->dado){
            maior_numero = numero_atual->dado ;
        }
        numero_atual = numero_atual->proximo_numero;
    }
    return maior_numero;
}

int counting_sort(){
    Numero *vet = inicio_lista;
    int maior_valor = 0; 
    maior_valor = maior_numero();
    int numero_atual[tamanho_lista];
    
    for(int i=0; i<tamanho_lista; i++){
        numero_atual[i] = vet->dado;
        vet = vet->proximo_numero;
    }
    
    int v_aux[maior_valor];    //C
    int ordenado[tamanho_lista];  //B


    for(int i = 0; i<=maior_valor; i++){   //Vetor de zeros
        v_aux[i] = 0;
        desempenho_counting.movimentos_no_vetor++;
    }
    for(int i =0; i<tamanho_lista; i++){
        v_aux[numero_atual[i]]++;
    }
    for(int i =0; i<=maior_valor; i++){
        v_aux[i] += v_aux[i-1];
    }

    for(int i = tamanho_lista-1; i>=0 ; i--){
        ordenado[v_aux[numero_atual[i]]-1] = numero_atual[i];
        v_aux[numero_atual[i]]--;
    }
    for(int i =0; i<tamanho_lista; i++){
        numero_atual[i] = ordenado[i];
    }
    FILE *arquivo = fopen("counting.txt", "w+");
    if(arquivo == NULL){
        printf("Erro de alocação de memória no arquivo do counting sort");
        return EXIT_FAILURE;
    }
    for(int i= 0; i<tamanho_lista; i++){
        fprintf(arquivo,"%i, ", numero_atual[i]);
    }
    fclose(arquivo);
}

int heap_sort(){
	int i, tmp;
    int n = tamanho_lista;
    int vet[tamanho_lista];
    Numero *copia_vetor = inicio_lista;

    for(int i = 0; i<tamanho_lista; i++){
        vet[i] = copia_vetor->dado;
        copia_vetor = copia_vetor->proximo_numero;
    }
	for (i = (n / 2); i >= 0; i--) {
		peneira(vet, i, n - 1);
	}

	for (i = n-1; i >= 1; i--) {
        desempenho_heap.movimentos_no_vetor++;
		tmp = vet[0];
		vet[0] = vet[i];
		vet[i] = tmp;
		peneira(vet, 0, i-1);
	}

    FILE *arquivo = fopen("heapsort.txt", "w+");
    if(arquivo == NULL){
        printf("Erro de alocação de memória no arquivo do heap sort");
        return EXIT_FAILURE;
    }
    
    for(int i= 0; i<tamanho_lista; i++){
        fprintf(arquivo,"%i, ", vet[i]);
    }
    
    fclose(arquivo);

}

void peneira(int *vet, int raiz, int fundo) {
	int pronto, filhoMax, tmp;

	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
        desempenho_heap.comparacoes_no_vetor++;
		if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
		}
		else if (vet[raiz * 2] > vet[raiz * 2 + 1]) {
            desempenho_heap.comparacoes_no_vetor++;
			filhoMax = raiz * 2;
		}
		else {
            desempenho_heap.comparacoes_no_vetor++;
			filhoMax = raiz * 2 + 1;
		}
    desempenho_heap.comparacoes_no_vetor++;
	if (vet[raiz] < vet[filhoMax]) {
        desempenho_heap.movimentos_no_vetor++;
		tmp = vet[raiz];
		vet[raiz] = vet[filhoMax];
		vet[filhoMax] = tmp;
		raiz = filhoMax;
    }
	else {
      pronto = 1;
	}
  }
}

void count_Sort(int arr[], int exp) 
{ 
    int output[tamanho_lista]; 
    int i, count[50000] = { 0 }; 
  
    
    for (i = 0; i < tamanho_lista; i++) 
        count[(arr[i] / exp) % 10]++; 
  
   
    for (i = 1; i < 50000; i++) 
        count[i] += count[i - 1]; 
  
 
    for (i = tamanho_lista - 1; i >= 0; i--) { 
        output[count[(arr[i] / exp) % 10] - 1] = arr[i]; 
        count[(arr[i] / exp) % 10]--; 
    } 
  
    for (i = 0; i < tamanho_lista; i++){
        desempenho_radix_counting.movimentos_no_vetor++;
        arr[i] = output[i]; 
    } 
        
}  
int radix_com_counting(){ 
    int m = maior_numero(); 
    Numero *copia_vetor = inicio_lista;
    int vetor[tamanho_lista];
    for(int i = 0; i<tamanho_lista; i++){
        vetor[i] = copia_vetor->dado;
        copia_vetor = copia_vetor->proximo_numero;
    }
    for (int exp = 1; m / exp > 0; exp *= 10){
        count_Sort(vetor,exp);
    }

    FILE *arquivo = fopen("radix_couting.txt", "w+");
    if(arquivo == NULL){
        printf("Erro de alocação de memória no arquivo do radix com couting sort");
        return EXIT_FAILURE;
    }

    for(int i= 0; i<tamanho_lista; i++){
        fprintf(arquivo,"%i, ", vetor[i]);
    }
    fclose(arquivo); 
} 

int radix_com_bucket(){

    Numero *copia_vetor_original = inicio_lista;
    int vetor[tamanho_lista];
    int i;
    int *b;
    int maior = copia_vetor_original->dado;
    int exp = 1;
    for(int i = 0; i<tamanho_lista; i++){
        vetor[i] = copia_vetor_original->dado;
        copia_vetor_original = copia_vetor_original->proximo_numero;
    }
    b = (int *)calloc(tamanho_lista, sizeof(int));

    for (i = 0; i < tamanho_lista; i++) {
        desempenho_radix_bucket.comparacoes_no_vetor++;
        if (vetor[i] > maior){
    	    maior = vetor[i];
        }
    }

    while (maior/exp > 0) {
        int bucket[1000] = { 0 };
    	for (i = 0; i < tamanho_lista; i++){
    	    bucket[(vetor[i] / exp) % 10]++;
        }
    	for (i = 1; i < 1000; i++){
    	    bucket[i] += bucket[i - 1];
        }
    	for (i = tamanho_lista - 1; i >= 0; i--){
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
        }
    	for (i = 0; i < tamanho_lista; i++){
            desempenho_radix_bucket.movimentos_no_vetor++;
    	    vetor[i] = b[i];
        }
    	exp *= 10;
    }

    FILE *arquivo = fopen("radix_com_bucket.txt", "w+");
    if(arquivo == NULL){
        printf("Erro de alocação de memória no arquivo do radix com bucket sort");
        return EXIT_FAILURE;
    }
    for(int i= 0; i<tamanho_lista; i++){
        fprintf(arquivo,"%i, ", vetor[i]);
    }
    fclose(arquivo);

    free(b);
}

int bucket_sort(){ 
    Numero *vet = inicio_lista;
    int v[tamanho_lista];
    int tam = tamanho_lista;
    for(int i=0; i<tamanho_lista; i++){
        v[i] = vet->dado;
        vet = vet->proximo_numero;
    }

    bucket *b; 
    b = malloc (tam *sizeof(bucket));                                     
    int i,j,k;                                                 
    for(i=0;i<tam;i++){                 /* 1 */   //inicializa todos os "topo"
        b[i].topo=0;
    }     
    for(i=0;i<tam;i++){                        /* 2 */   //verifica em que balde o elemento deve ficar
        j=(tam)-1;
        while(1){
            desempenho_bucket.comparacoes_no_vetor++;
            if(j<0){
                break;
            }
            if(v[i]>=j*10){
                b[j].balde[b[j].topo]=v[i];
                (b[j].topo)++;
                desempenho_bucket.movimentos_no_vetor++;
                break;
            }
            j--;
        }
    }
    for(i=0;i<tam;i++){                     //ordna os baldes  /* 3 */ 
        desempenho_bucket.comparacoes_no_vetor++;
        if(b[i].topo){
            bubble(b[i].balde,b[i].topo);
        }
    }
    i=0;
    for(j=0;j<tam;j++){                    //põe os elementos dos baldes de volta no vetor  /* 4 */ 
        for(k=0;k<b[j].topo;k++){
            v[i]=b[j].balde[k];
            i++;
        }
    }
    FILE *arquivo = fopen("=bucket.txt", "w+");
    if(arquivo == NULL){
        printf("Erro de alocação de memória no arquivo do bucket sort");
        return EXIT_FAILURE;
    }
    for(int i= 0; i<tamanho_lista; i++){
        fprintf(arquivo,"%i, ", v[i]);
    }
    fclose(arquivo);
 }
 
void bubble(int v[],int tam){
    int i,j,temp,flag;
    if(tam)
                 for(j=0;j<tam-1;j++){
                         flag=0;
                         for(i=0;i<tam-1;i++){
                             desempenho_bucket.comparacoes_no_vetor++;
                                 if(v[i+1]<v[i]){
                                     desempenho_bucket.movimentos_no_vetor++;
                                         temp=v[i];
                                         v[i]=v[i+1];
                                         v[i+1]=temp;
                                         flag=1;
                                 }
                         }
                         if(!flag)
                                 break;
                 }
 }

void menos_comparacoes(){
    
    printf("\n");
    long int comp[6];
    comp[0] = desempenho_cocktail.comparacoes_no_vetor;
    comp[1] = desempenho_counting.comparacoes_no_vetor;
    comp[2] = desempenho_heap.comparacoes_no_vetor;
    comp[3] = desempenho_bucket.comparacoes_no_vetor;
    comp[4] = desempenho_radix_counting.comparacoes_no_vetor;
    comp[5] = desempenho_radix_bucket.comparacoes_no_vetor;

    long int menor = comp[0];

    for(int i =0; i<6; i++){
        if(menor> comp[i]){
            menor = comp[i];
        }
    }
    for(int i = 0; i<6; i++){
        if(menor == comp[i]){
            switch (i){
                case 0:
                    printf("Menos comparações: Cocktail - %li\n", desempenho_cocktail.comparacoes_no_vetor);
                    break;
                case 1:
                    printf("Menos comparações: Counting - %li\n", desempenho_counting.comparacoes_no_vetor);
                    break;
                case 2:
                    printf("Menos comparações: Heap - %li\n", desempenho_heap.comparacoes_no_vetor);
                    break;
                case 3:
                    printf("Menos comparações: Bucket - %li\n", desempenho_bucket.comparacoes_no_vetor);
                    break;
                case 4:
                    printf("Menos comparações: Radix com Counting - %li\n", desempenho_radix_counting.comparacoes_no_vetor);
                    break;
                case 5:
                    printf("Menos comparações: Radix com Bucket - %li\n", desempenho_radix_bucket.comparacoes_no_vetor);
                    break;
            }
        }
    }
    printf("\n");
}
void menos_movimentacoes(){
    long int comp[6];
    comp[0] = desempenho_cocktail.movimentos_no_vetor;
    comp[1] = desempenho_counting.movimentos_no_vetor;
    comp[2] = desempenho_heap.movimentos_no_vetor;
    comp[3] = desempenho_bucket.movimentos_no_vetor;
    comp[4] = desempenho_radix_counting.movimentos_no_vetor;
    comp[5] = desempenho_radix_bucket.movimentos_no_vetor;

    long int menor = comp[0];

    for(int i =0; i<6; i++){
        if(menor> comp[i]){
            menor = comp[i];
        }
    }
    for(int i = 0; i<6; i++){
        if(menor == comp[i]){
            switch (i){
                case 0:
                    printf("Menos movimentações: Cocktail - %li\n", desempenho_cocktail.movimentos_no_vetor);
                    break;
                case 1:
                    printf("Menos movimentações: Counting - %li\n", desempenho_counting.movimentos_no_vetor);
                    break;
                case 2:
                    printf("Menos movimentações: Heap - %li\n", desempenho_heap.movimentos_no_vetor);
                    break;
                case 3:
                    printf("Menos movimentações: Bucket - %li\n", desempenho_bucket.movimentos_no_vetor);
                    break;
                case 4:
                    printf("Menos movimentações: Radix com Counting - %li\n", desempenho_radix_counting.movimentos_no_vetor);
                    break;
                case 5:
                    printf("Menos movimentações: Radix com Bucket - %li\n", desempenho_radix_bucket.movimentos_no_vetor);
                    break;
            }
        }
    }
    
}
void menos_tempo(){
    
    printf("\n");
    float comp[6];
    comp[0] = desempenho_cocktail.tempo_ordenar_vetor;
    comp[1] = desempenho_counting.tempo_ordenar_vetor;
    comp[2] = desempenho_heap.tempo_ordenar_vetor;
    comp[3] = desempenho_bucket.tempo_ordenar_vetor;
    comp[4] = desempenho_radix_counting.tempo_ordenar_vetor;
    comp[5] = desempenho_radix_bucket.tempo_ordenar_vetor;

    float menor = comp[0];

    for(int i =0; i<6; i++){
        if(menor> comp[i]){
            menor = comp[i];
        }
    }
    for(int i = 0; i<6; i++){
        if(menor == comp[i]){
            switch (i){
                case 0:
                    printf("Menos tempo: Cocktail - %f\n", desempenho_cocktail.tempo_ordenar_vetor);
                    break;
                case 1:
                    printf("Menos tempo: Counting - %f\n", desempenho_counting.tempo_ordenar_vetor);
                    break;
                case 2:
                    printf("Menos tempo: Heap - %f\n", desempenho_heap.tempo_ordenar_vetor);
                    break;
                case 3:
                    printf("Menos tempo: Bucket - %f\n", desempenho_bucket.tempo_ordenar_vetor);
                    break;
                case 4:
                    printf("Menos tempo: Radix com Counting - %f\n", desempenho_radix_counting.tempo_ordenar_vetor);
                    break;
                case 5:
                    printf("Menos tempo: Radix com Bucket - %f\n", desempenho_radix_bucket.tempo_ordenar_vetor);
                    break;
            }
        }
    }
}