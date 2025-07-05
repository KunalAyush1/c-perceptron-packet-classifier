#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define LEARNING_RATE 0.01
#define MAX_ITN 100

struct perceptron{
    double *weights;
    double bias;
    int num_of_features;
    int is_trained;

};

struct packet_feature{
    double src_ip_class;
    double dest_port;
    double protocol;
    double packet_size;
    double flags;

};

struct training_sample{
    struct packet_feature data;
    int label;


};

struct dataset{
    struct training_sample *samples;
    int num_samples;
    int max_samples;
};

struct perceptron* init_perceptron(int num_of_features){
    struct perceptron* p = malloc(sizeof(struct perceptron));
    if(!p) return NULL;

    p->num_of_features=num_of_features;
    p->weights = malloc(num_of_features * sizeof(double));
    if(!p->weights){
        free(p);
        return NULL;
    }

    srand(time(NULL));
    for(int i = 0 ; i < num_of_features; i++){
        p->weights[i] =((double)rand() / RAND_MAX) - 0.5;
    }
    p->bias =((double)rand() / RAND_MAX) - 0.5;
    p->is_trained = 0;

    return p;

};

void free_perceptron(struct perceptron* p){
    if(p){
        free(p->weights);
        free(p);
    }
}

int activation_fn(double x){
    if ( x > 0) return 1;
    else return 0;
}

double dot_product(struct packet_feature* data, struct perceptron* p ){
    double sum = 0.0;

    double feature_array[5];

    feature_array[0] = data->src_ip_class;
    feature_array[1] = data->dest_port;
    feature_array[2] = data->protocol;
    feature_array[3] = data->packet_size;
    feature_array[4] = data->flags;

    for(int i = 0 ; i < p->num_of_features; i++){
        sum += feature_array[i] * p->weights[i];
    }

    return sum;


}



int predict(struct perceptron* p, struct packet_feature* data){
    double weighted_sum = dot_product(data , p) + p->bias;
    return activation_fn(weighted_sum);
}

void train_sample(struct perceptron* p , struct training_sample* sample){

    int prediction = predict(p , &sample->data);

    int error = sample->label - prediction;

    if(error == 0) return;

    double feature_array[5];

    feature_array[0] = sample->data.src_ip_class;
    feature_array[1] = sample->data.dest_port;
    feature_array[2] = sample->data.protocol;
    feature_array[3] = sample->data.packet_size;
    feature_array[4] = sample->data.flags;

    for(int i = 0 ; i < p->num_of_features; i++){
        p->weights[i] += LEARNING_RATE * error * feature_array[i];
    
    }
    p->bias += LEARNING_RATE * error;


}

void train_perceptron(struct perceptron* p , struct dataset* data){
    printf("-----Training---\n");

    for(int epoch = 0 ; epoch < MAX_ITN; epoch++){
       int errors = 0;
       
       for( int i = 0 ; i < data->num_samples; i++){
        int old_prediction = predict(p , &data->samples[i].data);
        train_sample(p , &data->samples[i]);
        int new_prediction = predict(p , &data->samples[i].data);

        if(new_prediction != data->samples[i].label ){
            errors++;
        }
       }

       printf("Epoch %d: %d errors \n", epoch + 1 , errors);

       if(errors ==0){
        printf("----Training Completed---\n");
        break;
       }


    }
    p->is_trained  = 1;

}

int main(){
    srand(time(NULL));

    struct dataset data;
    data.num_samples = 4;
    data.max_samples = 4;

    data.samples = malloc(data.max_samples * sizeof(struct training_sample));
    if(!data.samples){
        printf("Memory allocation failed\n");
        return 1;
    }

    data.samples[0] = (struct training_sample){{0.1 , 80 , 1 , 500 , 1}, 1};
    data.samples[1] = (struct training_sample){{0.2 , 23 , 1 , 1500 , 1}, 0};
    data.samples[2] = (struct training_sample){{0.3 , 443 , 1 , 600 , 1}, 1};
    data.samples[3] = (struct training_sample){{0.4 , 22 , 0 , 2000 , 0}, 0};

    struct perceptron* p = init_perceptron(5);
    
    train_perceptron(p , &data);

    for(int i = 0 ; i < data.num_samples ; i++){
        int pred = predict(p , &data.samples[i].data);
        printf("Sample %d: Actual = %d, Predicted = %d \n", i +1  , data.samples[i].label,pred);

    }

    free_perceptron(p);
    free(data.samples);
    return 0;

}




