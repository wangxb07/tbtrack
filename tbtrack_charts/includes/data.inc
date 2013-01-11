<?php

/**
 * @file store classes for chart data
 */


/**
 * base datastore
 * @abstract
 */
abstract class BaseDataStore {
  private $_data = array();
  private $_options = array();

  public function __construct($data, $options=NULL) {
    $this->_data = $data;
    $this->_options = $options;
  }

  /**
   * data getter
   * @return array
   */
  public function getData() {
    return $this->_data;
  }

  /**
   * get js array
   * @return string
   */
  public function getJSArray() {
    return drupal_json_encode($this->getFormatedData());
  }

  /**
   * generate special format array for data store
   * @return array
   */
  abstract public function getFormatedData();
}

/**
 * column chart data store
 * data array struct
 * <pre>
 * array(
 *   'Year' => array('2004', '2005', '2006', '2007'),
 *   'Sales' => array('1000', '1170', '660', '1030'),
 *   'Expenses' => array('400', '460', '1120', '103'),
 * )
 * </pre>
 */
class ArrayDataStore extends BaseDataStore {

  /**
   * implements getFormatedData, shift labels to data array
   * @return Array
   */
  public function getFormatedData() {
    $data = $this->getData();
    if (empty($data)) {
      return array();
    }
    $labels = array_keys($data);

    $formatedData = array();
    foreach (current($data) as $key => $row) {
      foreach ($labels as $label) {
        $formatedData[$key][] = $data[$label][$key];
      }
    }
    array_unshift($formatedData, $labels);
    return $formatedData;
  }
}

