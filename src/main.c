#include "libcfg.h"

/* A function that prints help messages. */
void help(void *pname) {
  printf("Usage: %s [OPTION [VALUE]]\n\
  -c, --conf\n\
        Set the configuration file.\n\
  -p, --unit_power \n\
        energy of each symbol set one \n\
  -n, --number_of_subcarriers \n\
        number of ofdm subcarriers \n\
  -r, --symbol_rate \n\
        how many symbol in ne seconds \n\
  -s, --seconds \n\
        number of seconds simulation \n\
  -o, --order \n\
        modulation order \n\
  -i, --input_signal \n\
        input .bin file for input_signal \n\
  -a, --output_signal \n\
        name file for store output signal \n\
  -h, --help\n\
        Display this message and exit.\n\
  --license\n\
        Display the license information.\n", (char *) pname);
  exit(0);
}

/* A function that prints the license information. */
void license(void *args) {
  printf("This code is distributed under the MIT license.\n\
See %s\n", (const char*)args);
      exit(0);
}


int main(int argc, char *argv[])
{
      char *repo = "https://github.com/yousefsmt/OFDM-PHY/main/LICENSE";

      int optidx = 0;
      int i      = 0;
      char *config_path;

      program_config    prog_args;

      fft_config        fft_args;
      ifft_config       ifft_args;
      modulation_config mod_args;
      ofdm_config       ofdm_args;

      /* Configurations for functions to be called via command line flags. */
      const int nfunc = 2;
      const cfg_func_t funcs[2] = {
      {   'h',    "help",         help,           argv[0] },
      {   0,      "license",      license,        repo    }
      };

      /* Configuration parameters. */
      const int npar = 8;
      const cfg_param_t params[8] = {
      {   'c',    "conf",                  "config_path",           CFG_DTYPE_STR,  &config_path},
      {   'p',    "unit_power",            "unit_power",            CFG_DTYPE_BOOL, &prog_args.unit_power},
      {   'n',    "number_of_subcarriers", "number_of_subcarriers", CFG_DTYPE_INT,  &prog_args.number_of_subcarriers},
      {   'r',    "symbol_rate",           "symbol_rate",           CFG_DTYPE_INT,  &prog_args.symbol_rate},
      {   's',    "seconds",               "seconds",               CFG_DTYPE_INT,  &prog_args.seconds},
      {   'o',    "order",                 "order",                 CFG_DTYPE_INT,  &prog_args.order},
      {   'i',    "input_signal",          "input_signal",          CFG_DTYPE_STR,  &prog_args.input_signal},
      {   'a',    "output_signal",         "output_signal",         CFG_DTYPE_STR,  &prog_args.output_signal},
      };

      /* Initialise the configurations. */
      cfg_t *cfg = cfg_init();
      if (!cfg) {
      fprintf(stderr, "Error: failed to initialize the configurations.\n");
      return 1;
      }

      /* Register functions to be called via command line options. */
      if (cfg_set_funcs(cfg, funcs, nfunc)) PRINT_ERROR;
      PRINT_WARNING;

      /* Register configuration parameters. */
      if (cfg_set_params(cfg, params, npar)) PRINT_ERROR;
      PRINT_WARNING;

      /* Parse command line options. */
      if (cfg_read_opts(cfg, argc, argv, PRIOR_CMD, &optidx)) PRINT_ERROR;
      PRINT_WARNING;

      /* Print command line arguments that are not parsed. */
      if (optidx < argc - 1) {
      printf("Unused command line options:\n ");
      for (i = optidx; i < argc; i++)
            printf(" %s", argv[i]);
      printf("\n");
      }

      /* Read configuration file. */
      if (!cfg_is_set(cfg, &config_path)) config_path = DEFAULT_CONF_FILE;
      if (cfg_read_file(cfg, config_path, PRIOR_FILE)) PRINT_ERROR;
      PRINT_WARNING;

      /****** Start simulation ******/
      init(cfg, &prog_args, &fft_args, &ifft_args, &mod_args, &ofdm_args);
      /****** End of simulation ******/

      /* Release memory. */
      if (cfg_is_set(cfg, &config_path)) free(config_path);
      cfg_destroy(cfg);

      return 0;
}