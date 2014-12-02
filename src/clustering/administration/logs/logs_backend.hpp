// Copyright 2010-2014 RethinkDB, all rights reserved.
#ifndef CLUSTERING_ADMINISTRATION_LOGS_LOGS_BACKEND_HPP_
#define CLUSTERING_ADMINISTRATION_LOGS_LOGS_BACKEND_HPP_

#include <string>
#include <vector>

#include "rdb_protocol/artificial_table/backend_cfeed.hpp"
#include "clustering/administration/metadata.hpp"

class server_name_client_t;

class logs_artificial_table_backend_t :
    public timer_cfeed_artificial_table_backend_t
{
public:
    logs_artificial_table_backend_t(
            mailbox_manager_t *_mailbox_manager,
            watchable_map_t<peer_id_t, cluster_directory_metadata_t> *_directory,
            server_name_client_t *_name_client,
            admin_identifier_format_t _identifier_format) :
        mailbox_manager(_mailbox_manager),
        directory(_directory),
        name_client(_name_client),
        identifier_format(_identifier_format) { }
    ~logs_artificial_table_backend_t();

    std::string get_primary_key_name();

    bool read_all_rows_as_vector(signal_t *interruptor,
                                 std::vector<ql::datum_t> *rows_out,
                                 std::string *error_out);

    bool read_row(ql::datum_t primary_key,
                  signal_t *interruptor,
                  ql::datum_t *row_out,
                  std::string *error_out);

    bool write_row(ql::datum_t primary_key,
                   bool pkey_was_autogenerated,
                   ql::datum_t *new_value_inout,
                   signal_t *interruptor,
                   std::string *error_out);

private:
    mailbox_manager_t *mailbox_manager;
    watchable_map_t<peer_id_t, cluster_directory_metadata_t> *directory;
    server_name_client_t *name_client;
    admin_identifier_format_t identifier_format;
};

#endif /* CLUSTERING_ADMINISTRATION_LOGS_LOGS_BACKEND_HPP_ */

