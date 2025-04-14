const algoDetail = {
    "partition": {
        "c": {
            "seq": "Zaporedni program",
            "mlt_stc": "Več problemov se rešuje hkrati z nastavitvijo 'schedule(static)'",
            "mlt_dyn": "Več problemov se rešuje hkrati z nastavitvijo 'schedule(dynamic)'",
            "sgl_dyn": "En problem se rešuje hkrati z nastavitvijo 'schedule(dynamic)'",
            "sgl_stc": "En problem se rešuje hkrati z nastavitvijo 'schedule(static)'",
            "nested": "Gnezdeni paralelizem - več problemov se izvaja vzporedno 'schedule(dynamic)', pri čemer se tudi vsak posamičen problem izvaja vzporedno 'schedule(static)'",
        },
        "go": {
            "seq": "Zaporedni program",
            "mlt_all_chn": "Vsak partition problem je dinamično dodeljen svoji goroutine-i. Goroutine-i so sinhronizirani z uporabo kanalov",
            "mlt_dyn_chn": "Dinamično porazdeljevanje dela med goroutine - z uporabo kanalov. Goroutine-i so sinhronizirani z uporabo kanalov",
            "mlt_all": "Vsak partition problem je dinamično dodeljen svoji goroutine-i.",
            "sgl_all_chn": "Rešuje se en partition problem naenkrat, pri čemer se podmnožice rešujejo vzporedno z uporabo kanalov",
            "nested": "Vsakemu partition problemu pripada ena goroutina, ki ga kasneje rešuje hkrati več goroutin"
        },
        "julia": {
            "seq": "Zaporedni program",
            "par": "Paralelni program",
        },
    },
    "kamada_kawai": {
        "c": {
            "sgl_seq": "Premikamo en delec naenkrat, delte računamo sinhrono",
            "sgl_par": "Premikamo en delec naenkrat, delte računamo vzporedno",
            "mlt_seq": "Premikamo več delcev naenkrat, delte računamo sinhrono",
            "mlt_par": "Premikamo več delcev naenkrat, delte računamo vzporedno",
        },
        "go": {
            "sgl_seq": "Zaporedni program",
            "sgl_par": "Paralelni program",
        },
        "julia": {
            "sgl_seq": "Zaporedni program",
            "sgl_par": "Paralelni program",
        },
    },
}