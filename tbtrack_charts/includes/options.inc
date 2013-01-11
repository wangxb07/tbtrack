<?php

/**
 * @file The file declare classes for google chart api options convert from php
 * array to json
 */

class Options {
  private $_options = array();

  private $_json = "";

  public function __construct($options) {
    $this->_options = $options;
  }

  /**
   * php data convert to json
   * @return string
   */
  public function getJSON() {
    if (empty($this->_json)) {
      $options = array();
      foreach($this->_options as $key=>$option) {
        if ($key == 'width' || $key == 'height') {
          continue;
        }
        $options[$key] = $option;
      }

      $this->_json = drupal_json_encode((object)$options);
    }
    return $this->_json;
  }

  /**
   * implement __get
   */
  public function __get($name) {
    if (array_key_exists($name, $this->_options)) {
      return $this->_options[$name];
    }
    return NULL;
  }
}