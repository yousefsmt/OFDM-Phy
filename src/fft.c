#include "fft.h"

int init_fft(fft_config* config)
{
    config->fft_size = FFT_SIZE;
    config->input    = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
    config->output   = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);

    config->fft_plan_complex = fftw_plan_dft_1d(FFT_SIZE, config->input, config->output, FFTW_FORWARD, FFTW_ESTIMATE);

    return 0;
}

int run_fft(fft_config* config, double complex* input_array, double complex* output_array)
{
    memcpy(config->input, input_array, FFT_SIZE);

    fftw_execute(config->fft_plan_complex);

    memcpy(output_array, config->output, FFT_SIZE);

    return 0;
}

int close_fft(fft_config* config)
{
    fftw_destroy_plan(config->fft_plan_complex);
    fftw_free(config->input);
    fftw_free(config->output);

    return 0;
}