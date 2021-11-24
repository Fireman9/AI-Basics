(import csv)


(defn get_csv[filename]
	(do
    (setv file (open filename))
    (setv data (list (csv.reader file)))
    (file.close)
    data
	)
)

(defn process_data[unprocessed_data]
	(do
		(list 
			(map 
				(fn [item] 
					(do
						(setv temp [])
						(temp.append (float (get item 1)))
						(temp.append (int (get item 2)))
						temp
					)
				)
				unprocessed_data
			)
		)
	)
)

(defn get_column[array column_number]
  (do
    (list
      (map 
				(fn [item] 
					(do
						(get item column_number)
					)
				)
				array
			)
    )
  )
)

(defn get_probability[array]
  (do
    (/ 1 (len array))
  )
)

(defn get_math_expectation[array probability]
  (do
    (* 
      (sum 
        (lfor item array 
          (do item)
        )
      )
      probability
    )
  )
)

(defn get_math_expectation_time [data]
  (do
    (setv time_array (get_column data 0))
    (setv probability (get_probability time_array))
    (setv math_expectation (get_math_expectation time_array probability))
    math_expectation
  )
)

(defn get_dispersion_points[data]
  (do
    (setv points_array (get_column data 1))
    (setv probability (get_probability points_array))
    (setv math_expectation (get_math_expectation points_array probability))
    (setv math_expectation_squares 
      (get_math_expectation 
        (lfor item points_array
          (** (do item) 2)
        )
        probability
      )
    )
    (setv dispersion (- math_expectation_squares (** math_expectation 2)))
    dispersion
  )
)

(setv unprocessed_data (get_csv "./Stats.csv"))
(setv data (process_data unprocessed_data))
(print "Math expectation for time:" (get_math_expectation_time data))
(print "Dispersion for score:" (get_dispersion_points data))
