// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SPELLCHECKER_FEEDBACK_SENDER_H_
#define CHROME_BROWSER_SPELLCHECKER_FEEDBACK_SENDER_H_

#include <map>
#include <set>
#include <vector>

#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/timer.h"
#include "chrome/browser/spellchecker/feedback.h"
#include "chrome/browser/spellchecker/misspelling.h"
#include "googleurl/src/gurl.h"
#include "net/url_request/url_fetcher_delegate.h"

class SpellCheckMarker;
class SpellingServiceFeedbackTest;
struct SpellCheckResult;

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}

namespace spellcheck {

// Constants for the feedback field trial.
static const char kFeedbackFieldTrialName[] = "SpellingServiceFeedback";
static const char kFeedbackFieldTrialEnabledGroupName[] = "Enabled";

// Manages sending feedback to the spelling service.
class FeedbackSender : public base::SupportsWeakPtr<FeedbackSender>,
                       public net::URLFetcherDelegate {
 public:
  FeedbackSender(net::URLRequestContextGetter* request_context,
                 const std::string& language,
                 const std::string& country);
  virtual ~FeedbackSender();

  // Records that user selected suggestion |suggestion_index| for the
  // misspelling identified by |hash|.
  void SelectedSuggestion(uint32 hash, int suggestion_index);

  // Records that user added the misspelling identified by |hash| to the
  // dictionary.
  void AddedToDictionary(uint32 hash);

  // Records that user right-clicked on the misspelling identified by |hash|,
  // but did not select any suggestion.
  void IgnoredSuggestions(uint32 hash);

  // Records that user did not choose any suggestion but manually corrected the
  // misspelling identified by |hash| to string |correction|, which is not in
  // the list of suggestions.
  void ManuallyCorrected(uint32 hash, const string16& correction);

  // Receives document markers for renderer with process ID |render_process_id|
  // when the renderer responds to a RequestDocumentMarkers() call. Finalizes
  // feedback for the markers that are gone from the renderer. Sends feedback
  // data for the renderer with process ID |renderer_process_id| to the spelling
  // service. If the current session has expired, then refreshes the session
  // start timestamp and sends out all of the feedback data.
  void OnReceiveDocumentMarkers(int renderer_process_id,
                                const std::vector<uint32>& markers);

  // Generates feedback data based on spellcheck results. The new feedback data
  // is pending. Sets hash identifiers for |results|. Called when spelling
  // service client receives results from the spelling service.
  void OnSpellcheckResults(std::vector<SpellCheckResult>* results,
                           int renderer_process_id,
                           const string16& text,
                           const std::vector<SpellCheckMarker>& markers);

  // Receives updated language and country code for feedback. Finalizes and
  // sends out all of the feedback data.
  void OnLanguageCountryChange(const std::string& language,
                               const std::string& country);

 private:
  friend class FeedbackSenderTest;

  // net::URLFetcherDelegate implementation.
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  // Requests the document markers from all of the renderers to determine which
  // feedback can be finalized. Finalizes feedback for renderers that are gone.
  // Called periodically when |timer_| fires.
  void RequestDocumentMarkers();

  // Sends out all feedback data. Resets the session-start timestamp to now.
  // Restarts the timer that requests markers from the renderers.
  void FlushFeedback();

  // Sends out the |feedback_data|.
  void SendFeedback(const std::vector<Misspelling>& feedback_data,
                    bool is_first_feedback_batch);

  // Request context for the feedback senders.
  scoped_refptr<net::URLRequestContextGetter> request_context_;

  // The language of text. The string is a BCP 47 language tag.
  std::string language_;

  // The country of origin. The string is the ISO 3166-1 alpha-3 code.
  std::string country_;

  // Misspelling counter used to generate unique hash identifier for each
  // misspelling.
  size_t misspelling_counter_;

  // Feedback data.
  Feedback feedback_;

  // A set of renderer process IDs for renderers that have sent out feedback in
  // this session.
  std::set<int> renderers_sent_feedback_;

  // When the session started.
  base::Time session_start_;

  // The URL where the feedback data should be sent.
  GURL feedback_service_url_;

  // A timer to periodically request a list of document spelling markers from
  // all of the renderers. The timer runs while an instance of this class is
  // alive.
  base::RepeatingTimer<FeedbackSender> timer_;

  // Feedback senders that need to stay alive for the duration of sending data.
  // If a sender is destroyed before it finishes, then sending feedback will be
  // canceled.
  ScopedVector<net::URLFetcher> senders_;

  DISALLOW_COPY_AND_ASSIGN(FeedbackSender);
};

}  // namespace spellcheck

#endif  // CHROME_BROWSER_SPELLCHECKER_FEEDBACK_SENDER_H_
