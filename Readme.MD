# ATLAS: Axiom Backend Engine

## Operation
1. Data Ingestion
   1. Import Data
     * Check the types of each column
     * If any column is string.
       * Make a copy by removing special characters (Replace empty with nulls). On the copy,
       * If numeric regex matches for at least 50% → Infer type number
       * If timestamp regex matches for at least 50% → Infer type timestamp
       * If date regex matches for at least 50% → Infer type date
       * If time regex matches for at least 50% → Infer type time
       * If special boolean patterns matches → Infer type boolean
       * else → Infer type string
       * Discard copy
       * if inferred type is string → Get unique counts
       * If a type other than string inferred, CAST the copy to that type
       * return copy if type != string else return original
     * If any column is duration,
       * CAST the column to double and return
     * If any column is time32 OR date32,
       * CAST the column to int64
     * If column is boolean,
       * CAST t
     
     * If unique count == total count → Remove
