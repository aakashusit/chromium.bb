// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// An implementation of SyncNotifier that wraps InvalidationNotifier
// on its own thread.

#ifndef SYNC_NOTIFIER_NON_BLOCKING_INVALIDATOR_H_
#define SYNC_NOTIFIER_NON_BLOCKING_INVALIDATOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "jingle/notifier/base/notifier_options.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/util/weak_handle.h"
#include "sync/notifier/invalidation_handler.h"
#include "sync/notifier/invalidation_state_tracker.h"
#include "sync/notifier/invalidator.h"
#include "sync/notifier/invalidator_registrar.h"

namespace base {
class SingleThreadTaskRunner;
}  // namespace base

namespace syncer {
class SyncNetworkChannel;
class GCMNetworkChannelDelegate;

// Callback type for function that creates SyncNetworkChannel. This function
// gets passed into NonBlockingInvalidator constructor.
typedef base::Callback<scoped_ptr<SyncNetworkChannel>(void)>
    NetworkChannelCreator;

class SYNC_EXPORT_PRIVATE NonBlockingInvalidator
    : public Invalidator,
      // InvalidationHandler to "observe" our Core via WeakHandle.
      public InvalidationHandler {
 public:
  // |invalidation_state_tracker| must be initialized.
  NonBlockingInvalidator(
      NetworkChannelCreator network_channel_creator,
      const std::string& invalidator_client_id,
      const UnackedInvalidationsMap& saved_invalidations,
      const std::string& invalidation_bootstrap_data,
      const WeakHandle<InvalidationStateTracker>&
          invalidation_state_tracker,
      const std::string& client_info,
      const scoped_refptr<net::URLRequestContextGetter>&
          request_context_getter);

  virtual ~NonBlockingInvalidator();

  // Invalidator implementation.
  virtual void RegisterHandler(InvalidationHandler* handler) OVERRIDE;
  virtual void UpdateRegisteredIds(InvalidationHandler* handler,
                                   const ObjectIdSet& ids) OVERRIDE;
  virtual void UnregisterHandler(InvalidationHandler* handler) OVERRIDE;
  virtual InvalidatorState GetInvalidatorState() const OVERRIDE;
  virtual void UpdateCredentials(
      const std::string& email, const std::string& token) OVERRIDE;
  virtual void RequestDetailedStatus(
      base::Callback<void(const base::DictionaryValue&)> callback) const
      OVERRIDE;

  // InvalidationHandler implementation.
  virtual void OnInvalidatorStateChange(InvalidatorState state) OVERRIDE;
  virtual void OnIncomingInvalidation(
      const ObjectIdInvalidationMap& invalidation_map) OVERRIDE;
  virtual std::string GetOwnerName() const OVERRIDE;

  // Static functions to construct callback that creates network channel for
  // SyncSystemResources. The goal is to pass network channel to invalidator at
  // the same time not exposing channel specific parameters to invalidator and
  // channel implementation to client of invalidator.
  static NetworkChannelCreator MakePushClientChannelCreator(
      const notifier::NotifierOptions& notifier_options);
  static NetworkChannelCreator MakeGCMNetworkChannelCreator(
      scoped_refptr<net::URLRequestContextGetter> request_context_getter,
      scoped_ptr<GCMNetworkChannelDelegate> delegate);
 private:
  struct InitializeOptions;
  class Core;

  InvalidatorRegistrar registrar_;

  // The real guts of NonBlockingInvalidator, which allows this class to live
  // completely on the parent thread.
  scoped_refptr<Core> core_;
  scoped_refptr<base::SingleThreadTaskRunner> parent_task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> network_task_runner_;

  base::WeakPtrFactory<NonBlockingInvalidator> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(NonBlockingInvalidator);
};

}  // namespace syncer

#endif  // SYNC_NOTIFIER_NON_BLOCKING_INVALIDATOR_H_
